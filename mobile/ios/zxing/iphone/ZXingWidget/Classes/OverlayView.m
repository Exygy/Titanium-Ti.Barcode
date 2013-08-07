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

static const CGFloat kPadding = 0;

@interface OverlayView()
@property (nonatomic,assign) UIButton *cancelButton;
@property (nonatomic,assign) UIButton *flashButton;
@property (nonatomic,retain) UILabel *instructionsLabel;
@end


@implementation OverlayView

@synthesize delegate, oneDMode;
@synthesize points = _points;
@synthesize cancelButton;
@synthesize flashButton;
@synthesize cropRect;
@synthesize instructionsLabel;
@synthesize displayedMessage;

////////////////////////////////////////////////////////////////////////////////////////////////////
- (id) initWithFrame:(CGRect)theFrame
       cancelEnabled:(BOOL)isCancelEnabled
        flashEnabled:(BOOL)isFlashEnabled
    rectangleEnabled:(BOOL)isRectangleEnabled
            oneDMode:(BOOL)isOneDModeEnabled
         withOverlay:(UIView*)overlay {
    self = [super initWithFrame:theFrame];
    if( self ) {
        rectangleEnabled = isRectangleEnabled;
        CGFloat rectSize = self.frame.size.width - kPadding * 2;
        if (!oneDMode) {
            cropRect = CGRectMake(kPadding, (self.frame.size.height - rectSize) / 2, rectSize, rectSize);
        } else {
            CGFloat rectSize2 = self.frame.size.height - kPadding * 2;
            cropRect = CGRectMake(kPadding, kPadding, rectSize, rectSize2);		
        }
        
        self.backgroundColor = [UIColor clearColor];
        self.oneDMode = isOneDModeEnabled;
        if (isCancelEnabled) {
            UIButton *butt = [UIButton buttonWithType:UIButtonTypeCustom]; 
            self.cancelButton = butt;
            [cancelButton setTitle:@"Cancel" forState:UIControlStateNormal];
            if (oneDMode) {
                [cancelButton setTransform:CGAffineTransformMakeRotation(M_PI/2)];
                
                [cancelButton setFrame:CGRectMake(20, 175, 45, 130)];
            }
            else {
                CGSize theSize = CGSizeMake(70, 40);
                CGRect theRect = CGRectMake(5, (((self.frame.size.height - rectSize) / 4) - (theSize.height/2)), theSize.width, theSize.height);
                [cancelButton setFrame:theRect];
            }
            
            [cancelButton setTitleColor:[UIColor whiteColor] forState:UIControlStateNormal];
            
            [cancelButton addTarget:self action:@selector(cancel:) forControlEvents:UIControlEventTouchUpInside];
            [self addSubview:cancelButton];
            [self addSubview:imageView];
        }
        
        if (isFlashEnabled) {
            UIButton *butt = [UIButton buttonWithType:UIButtonTypeCustom];
            self.flashButton = butt;
                    
            [flashButton setTitle:@"Turn Flash On" forState:UIControlStateNormal];
            
            CGSize theSize = CGSizeMake(130, 40);
            CGRect theRect = CGRectMake((theFrame.size.width - theSize.width), (((self.frame.size.height - rectSize) / 4) - (theSize.height/2)), theSize.width, theSize.height);
            [flashButton setFrame:theRect];
            [flashButton setTitleColor:[UIColor whiteColor] forState:UIControlStateNormal];
            
            [flashButton addTarget:self action:@selector(switchFlash:) forControlEvents:UIControlEventTouchUpInside];
            [self addSubview:flashButton];
        }
    }
    return self;
}

- (void)cancel:(id)sender {
	// call delegate to cancel this scanner
	if (delegate != nil) {
		[delegate cancelled];
	}
}

- (void)switchFlash:(id)sender {
    if([flashButton.titleLabel.text isEqualToString:@"Turn Flash On"]){
        [flashButton setTitle:@"Turn Flash Off" forState:UIControlStateNormal];
    }else{
        [flashButton setTitle:@"Turn Flash On" forState:UIControlStateNormal];
    }
    [self setTorch:![self torchIsOn]];
}

#pragma mark - Torch

- (void)setTorch:(BOOL)status {
    // Is this call redundant? Than ignore it...
//    if (status == [self torchIsOn]) {
//        return;
//    }
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


////////////////////////////////////////////////////////////////////////////////////////////////////
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
        
        
        //CGContextAddLineToPoint(context, rect.origin.x + rect.size.width, rect.origin.y + rect.size.height);
        CGContextMoveToPoint(context, rect.origin.x + rect.size.width, rect.origin.y + rect.size.height);
        
        CGContextAddLineToPoint(context, rect.origin.x, rect.origin.y + rect.size.height);
        
        //CGContextAddLineToPoint(context, rect.origin.x, rect.origin.y);
        
        CGContextStrokePath(context);
    }
}

- (CGPoint)map:(CGPoint)point {
    CGPoint center;
    center.x = cropRect.size.width/2;
    center.y = cropRect.size.height/2;
    float x = point.x - center.x;
    float y = point.y - center.y;
    int rotation = 90;
    switch(rotation) {
        case 0:
            point.x = x;
            point.y = y;
            break;
        case 90:
            point.x = -y;
            point.y = x;
            break;
        case 180:
            point.x = -x;
            point.y = -y;
            break;
        case 270:
            point.x = y;
            point.y = -x;
            break;
    }
    point.x = point.x + center.x;
    point.y = point.y + center.y;
    return point;
}

#define kTextMargin 10

////////////////////////////////////////////////////////////////////////////////////////////////////
- (void)drawRect:(CGRect)rect {
	[super drawRect:rect];
    if (displayedMessage == nil) {
        self.displayedMessage = @"Place a barcode inside the viewfinder to scan it.";
    }
	CGContextRef c = UIGraphicsGetCurrentContext();
    
	if (_points != nil) {
        //		[imageView.image drawAtPoint:cropRect.origin];
	}
	
    int offset = rect.size.width / 2;
    if (rectangleEnabled) {
        CGFloat white[4] = {1.0f, 1.0f, 1.0f, 1.0f};
        CGContextSetStrokeColor(c, white);
        CGContextSetFillColor(c, white);
        [self drawRect:cropRect inContext:c];
        
        //	CGContextSetStrokeColor(c, white);
        //	CGContextSetStrokeColor(c, white);
        CGContextSaveGState(c);
        if (oneDMode) {
            char *text = "Place a red line over the bar code to be scanned.";
            CGContextSelectFont(c, "Helvetica", 15, kCGEncodingMacRoman);
            CGContextScaleCTM(c, -1.0, 1.0);
            CGContextRotateCTM(c, M_PI/2);
            CGContextShowTextAtPoint(c, 74.0, 285.0, text, 49);
        }
        else {
            UIFont *font = [UIFont systemFontOfSize:18];
            CGSize constraint = CGSizeMake(rect.size.width, cropRect.origin.y);
            CGSize displaySize = [self.displayedMessage sizeWithFont:font constrainedToSize:constraint];
            CGRect displayRect = CGRectMake((rect.size.width - displaySize.width) / 2 , (cropRect.origin.y + cropRect.size.height + 20), displaySize.width, displaySize.height);
            [self.displayedMessage drawInRect:displayRect withFont:font lineBreakMode:UILineBreakModeWordWrap alignment:UITextAlignmentCenter];
        }
        CGContextRestoreGState(c);
        if (oneDMode) {
            CGFloat red[4] = {1.0f, 0.0f, 0.0f, 1.0f};
            CGContextSetStrokeColor(c, red);
            CGContextSetFillColor(c, red);
            CGContextBeginPath(c);
            //		CGContextMoveToPoint(c, rect.origin.x + kPadding, rect.origin.y + offset);
            //		CGContextAddLineToPoint(c, rect.origin.x + rect.size.width - kPadding, rect.origin.y + offset);
            CGContextMoveToPoint(c, rect.origin.x + offset, rect.origin.y + kPadding);
            CGContextAddLineToPoint(c, rect.origin.x + offset, rect.origin.y + rect.size.height - kPadding);
            CGContextStrokePath(c);
        }
    }
    if (_points != nil) {
        CGFloat blue[4] = {0.0f, 1.0f, 0.0f, 1.0f};
        CGContextSetStrokeColor(c, blue);
        CGContextSetFillColor(c, blue);
        if (oneDMode) {
            CGPoint val1 = [self map:[[_points objectAtIndex:0] CGPointValue]];
            CGPoint val2 = [self map:[[_points objectAtIndex:1] CGPointValue]];
            CGContextMoveToPoint(c, offset, val1.x);
            CGContextAddLineToPoint(c, offset, val2.x);
            CGContextStrokePath(c);
        }
        else {
            CGRect smallSquare = CGRectMake(0, 0, 0, 0);
            for( NSValue* value in _points ) {
                CGPoint point = [self map:[value CGPointValue]];
                smallSquare.origin = CGPointMake(
                                                 cropRect.origin.x + point.x - smallSquare.size.width / 2,
                                                 cropRect.origin.y + point.y - smallSquare.size.height / 2);
                [self drawRect:smallSquare inContext:c];
            }
        }
    }
}


////////////////////////////////////////////////////////////////////////////////////////////////////
/*
 - (void) setImage:(UIImage*)image {
 //if( nil == imageView ) {
 // imageView = [[UIImageView alloc] initWithImage:image];
 // imageView.alpha = 0.5;
 // } else {
 imageView.image = image;
 //}
 
 //CGRect frame = imageView.frame;
 //frame.origin.x = self.cropRect.origin.x;
 //frame.origin.y = self.cropRect.origin.y;
 //imageView.frame = CGRectMake(0,0, 30, 50);
 
 //[_points release];
 //_points = nil;
 //self.backgroundColor = [UIColor clearColor];
 
 //[self setNeedsDisplay];
 }
 */

////////////////////////////////////////////////////////////////////////////////////////////////////
- (UIImage*) image {
	return imageView.image;
}


////////////////////////////////////////////////////////////////////////////////////////////////////
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
