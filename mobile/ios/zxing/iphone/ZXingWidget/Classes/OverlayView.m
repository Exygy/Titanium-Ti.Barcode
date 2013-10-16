/**
 * Copyright 2009 Jeff Verkoeyen
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#import "OverlayView.h"

#import <AVFoundation/AVFoundation.h>

static const CGFloat kPadding = 10;

@interface OverlayView()
@property (nonatomic,assign) UIButton *cancelButton;
@property (nonatomic,assign) UIButton *flashButton;
@property (nonatomic,assign) UIButton *helpButton;
@property (nonatomic,retain) UILabel *instructionsLabel;
@end


@implementation OverlayView

@synthesize delegate, oneDMode;
@synthesize points = _points;
@synthesize cancelButton;
@synthesize flashButton;
@synthesize helpButton;
@synthesize cropRect;
@synthesize instructionsLabel;
@synthesize displayedMessage;

////////////////////////////////////////////////////////////////////////////////////////////////////
- (id) initWithFrame:(CGRect)theFrame
       cancelEnabled:(BOOL)isCancelEnabled
        flashEnabled:(BOOL)isFlashEnabled
         helpEnabled:(BOOL)isHelpEnabled
    rectangleEnabled:(BOOL)isRectangleEnabled
            oneDMode:(BOOL)isOneDModeEnabled
         withOverlay:(UIView*)overlay {
    self = [super initWithFrame:theFrame];
    if( self ) {
        rectangleEnabled = isRectangleEnabled;
        CGFloat rectSize = self.frame.size.width - kPadding * 2;
        int rectMargin = 60;
        cropRect = CGRectMake(kPadding+(rectMargin/2), (self.frame.size.height - rectSize) / 2, rectSize-rectMargin, rectSize);
        
        self.backgroundColor = [UIColor clearColor];
        self.oneDMode = isOneDModeEnabled;
        if (isCancelEnabled) {
            UIButton *butt = [UIButton buttonWithType:UIButtonTypeCustom]; 
            self.cancelButton = butt;
            [cancelButton setTitle:@"" forState:UIControlStateNormal];
            CGSize theSize = CGSizeMake(32, 34);
            CGRect theRect = CGRectMake((theFrame.size.width - theSize.width)-10, 10, theSize.width, theSize.height);
            [cancelButton setFrame:theRect];
            [cancelButton setTitleColor:[UIColor whiteColor] forState:UIControlStateNormal];
            [cancelButton setBackgroundImage:[UIImage imageNamed:@"/images/camera_close.png"] forState:UIControlStateNormal];
            cancelButton.transform = CGAffineTransformMakeRotation(90.0*M_PI/180.0);
            [cancelButton addTarget:self action:@selector(cancel:) forControlEvents:UIControlEventTouchUpInside];
            [self addSubview:cancelButton];
            [self addSubview:imageView];
        }
        
        if (isFlashEnabled) {
            UIButton *butt = [UIButton buttonWithType:UIButtonTypeCustom];
            self.flashButton = butt;
            flashButton.titleLabel.lineBreakMode = NSLineBreakByWordWrapping;
            flashButton.titleLabel.textAlignment = NSTextAlignmentCenter;
            [flashButton setTitle: @"" forState: UIControlStateNormal];
            CGSize theSize = CGSizeMake(34, 35);
            CGRect theRect = CGRectMake((theFrame.size.width-theSize.width-10), (theFrame.size.height-theSize.height-10), theSize.width, theSize.height);
            [flashButton setFrame:theRect];
            [flashButton setTitleColor:[UIColor whiteColor] forState:UIControlStateNormal];
            [flashButton setBackgroundImage:[UIImage imageNamed:@"/images/camera_flash.png"] forState:UIControlStateNormal];
            flashButton.transform = CGAffineTransformMakeRotation(90.0*M_PI/180.0);            
            [flashButton addTarget:self action:@selector(switchFlash:) forControlEvents:UIControlEventTouchUpInside];
            [self addSubview:flashButton];
        }
        
        if (isHelpEnabled) {
            UIButton *butt = [UIButton buttonWithType:UIButtonTypeCustom];
            self.helpButton = butt;
            helpButton.titleLabel.lineBreakMode = NSLineBreakByWordWrapping;
            helpButton.titleLabel.textAlignment = NSTextAlignmentCenter;
            [helpButton setTitle: @"" forState: UIControlStateNormal];
            CGSize theSize = CGSizeMake(35, 35);
            CGRect theRect = CGRectMake(10, (theFrame.size.height-theSize.height-10), theSize.width, theSize.height);
            [helpButton setFrame:theRect];
            [helpButton setTitleColor:[UIColor whiteColor] forState:UIControlStateNormal];
            [helpButton setBackgroundImage:[UIImage imageNamed:@"/images/camera_help.png"] forState:UIControlStateNormal];
            helpButton.transform = CGAffineTransformMakeRotation(90.0*M_PI/180.0);
            [helpButton addTarget:self action:@selector(showHelp:) forControlEvents:UIControlEventTouchUpInside];
            [self addSubview:helpButton];
        }
        
        // add Label
        CGSize theSize = CGSizeMake(380, 15);
        CGRect theRect = CGRectMake(-(theSize.width/2)-(theSize.height/2)+(rectMargin/2), ((self.frame.size.height - theSize.height) / 2), theSize.width, theSize.height);
        UILabel *label = [[UILabel alloc] initWithFrame:theRect];
        label.numberOfLines=0;
        label.lineBreakMode=UILineBreakModeCharacterWrap;
        [label setText:@"Place a barcode inside the viewfinder to scan it."];
        [label setTextColor:[UIColor whiteColor]];
        [label setBackgroundColor:[UIColor clearColor]];
        [label setTextAlignment:NSTextAlignmentCenter];
        label.transform = CGAffineTransformMakeRotation(90.0*M_PI/180.0);
        self.instructionsLabel = label;
        [self addSubview:label];
        [label release];        
    }
    return self;
}

- (void)cancel:(id)sender {
	// call delegate to cancel this scanner
	if (delegate != nil) {
		[delegate cancelled];
	}
}

- (void)showHelp:(id)sender {
	if (delegate != nil) {
		[delegate showHelp];
	}
}

#pragma mark - Torch

- (void)switchFlash:(id)sender {
    [self setTorch:![self torchIsOn]];
}

- (void)setTorch:(BOOL)status {
    // Is this call redundant? Than ignore it...
    if (status == [self torchIsOn]) {
        return;
    }
    Class captureDeviceClass = NSClassFromString(@"AVCaptureDevice");
    if (captureDeviceClass != nil) {
        AVCaptureDevice *device = [AVCaptureDevice defaultDeviceWithMediaType:AVMediaTypeVideo];
        [device lockForConfiguration:nil];
        if ( [device hasTorch] ) {
            if ( status ) {
                [device setTorchMode:AVCaptureTorchModeOn];
                [device setFlashMode:AVCaptureFlashModeOn];
            } else {
                [device setTorchMode:AVCaptureTorchModeOff];
                [device setFlashMode:AVCaptureFlashModeOff];
            }
        }
        [device unlockForConfiguration];
    }
}

- (BOOL)torchIsOn {
    Class captureDeviceClass = NSClassFromString(@"AVCaptureDevice");
    if (captureDeviceClass != nil) {
        AVCaptureDevice *device = [AVCaptureDevice defaultDeviceWithMediaType:AVMediaTypeVideo];
        if ( [device hasTorch] ) {
            return [device torchMode] == AVCaptureTorchModeOn;
        }
        [device unlockForConfiguration];
    }
    return NO;
}


#pragma mark - Memory

- (void) dealloc {
	[imageView release];
	[_points release];
    [instructionsLabel release];
    [displayedMessage release];
	[super dealloc];
}


- (void)drawRect:(CGRect)rect inContext:(CGContextRef)context {
    if (rectangleEnabled) {
        CGContextBeginPath(context);
        CGContextMoveToPoint(context, rect.origin.x, rect.origin.y);
        CGContextAddLineToPoint(context, rect.origin.x + rect.size.width, rect.origin.y);
        CGContextAddLineToPoint(context, rect.origin.x + rect.size.width, rect.origin.y + rect.size.height);
        CGContextAddLineToPoint(context, rect.origin.x, rect.origin.y + rect.size.height);
        CGContextAddLineToPoint(context, rect.origin.x, rect.origin.y);        
        CGContextStrokePath(context);
        
        int offset = rect.size.width / 2;
        CGFloat red[4] = {1.0f, 0.0f, 0.0f, 1.0f};
        CGContextSetStrokeColor(context, red);
        CGContextSetFillColor(context, red);
        CGContextBeginPath(context);
        CGContextMoveToPoint(context, rect.origin.x + offset, rect.origin.y + kPadding);
        CGContextAddLineToPoint(context, rect.origin.x + offset, rect.origin.y + rect.size.height - kPadding);
        CGContextStrokePath(context);
    }
}

#define kTextMargin 10

- (void)drawRect:(CGRect)rect {
	[super drawRect:rect];
	CGContextRef c = UIGraphicsGetCurrentContext();    
    if (rectangleEnabled) {
        CGFloat white[4] = {1.0f, 1.0f, 1.0f, 1.0f};
        CGContextSetStrokeColor(c, white);
        CGContextSetFillColor(c, white);
        [self drawRect:cropRect inContext:c];
    }
}

- (UIImage*) image {
	return imageView.image;
}

- (void) setPoints:(NSMutableArray*)pnts {
    [pnts retain];
    [_points release];
    _points = pnts;
	
    if (pnts != nil) {
        self.backgroundColor = [UIColor colorWithWhite:1.0 alpha:0.25];
    }
    [self setNeedsDisplay];
}

- (void) setPoint:(CGPoint)point {
    if (!_points) {
        _points = [[NSMutableArray alloc] init];
    }
    if (_points.count > 3) {
        [_points removeObjectAtIndex:0];
    }
    [_points addObject:[NSValue valueWithCGPoint:point]];
    [self setNeedsDisplay];
}


@end
