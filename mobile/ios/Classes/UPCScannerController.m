//
//  UPCScannerController.m
//  barcode
//
//  Created by Pierre Exygy on 9/29/13.
//
//

#import "UPCScannerController.h"


@interface UPCScannerController ()

@end

@implementation UPCScannerController

@synthesize delegate;
@synthesize overlayView;

- (id)initWithDelegate:(id<UPCScannerDelegate>)scanDelegate
            showCancel:(BOOL)shouldShowCancel
             showFlash:(BOOL)shouldShowFlash
              showHelp:(BOOL)shouldShowHelp{
    self = [super init];
    
    if (self) {
        [self setDelegate:scanDelegate];
        OverlayView *theOverlayView = [[OverlayView alloc] initWithFrame:[UIScreen mainScreen].bounds
                                                           cancelEnabled:shouldShowCancel
                                                            flashEnabled:shouldShowFlash
                                                             helpEnabled:shouldShowHelp
                                                        rectangleEnabled:TRUE
                                                                oneDMode:TRUE
                                                             withOverlay:nil];
        [theOverlayView setDelegate:self];
        self.overlayView = theOverlayView;
        [theOverlayView release];
    }
    
    return self;
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation {
    return NO; //(interfaceOrientation == UIInterfaceOrientationPortrait);
}

- (NSUInteger)supportedInterfaceOrientations
{
    return UIInterfaceOrientationMaskPortrait;
}

- (UIInterfaceOrientation)preferredInterfaceOrientationForPresentation
{
    return UIInterfaceOrientationPortrait;
}

- (BOOL)prefersStatusBarHidden {
    return YES;
}


- (void)viewDidAppear:(BOOL)animated
{    
    [super viewDidAppear:animated];
    [[UIApplication sharedApplication] setStatusBarHidden:YES withAnimation:UIStatusBarAnimationSlide];
    
    [self.view addSubview:self.overlayView];
    [self.overlayView setPoints:nil];
    
    NSError *error = nil;
    
    // Device
    self.device = [AVCaptureDevice defaultDeviceWithMediaType:AVMediaTypeVideo];
    
    [self.device lockForConfiguration:&error];
    CGPoint point = CGPointMake(0.5,0.5);
    [self.device setFocusPointOfInterest:point];
    [self.device setFocusMode:AVCaptureFocusModeContinuousAutoFocus];
    [self.device unlockForConfiguration];
    
    // Input
    self.input = [AVCaptureDeviceInput deviceInputWithDevice:self.device error:&error];
    
    // Output
    self.output = [[AVCaptureMetadataOutput alloc] init];
    [self.output setMetadataObjectsDelegate:self queue:dispatch_get_main_queue()];

    // Session
    self.session = [[AVCaptureSession alloc] init];
    if (self.input) {
        [self.session addInput:self.input];
    } else {
        NSLog(@"Error: %@", error);
    }
    [self.session addOutput:self.output];
    
    // Preview
    self.preview = [AVCaptureVideoPreviewLayer layerWithSession:self.session];
    self.preview.videoGravity = AVLayerVideoGravityResizeAspectFill;
    self.preview.frame = CGRectMake(0, 0, self.view.frame.size.width, self.view.frame.size.height);
    [self.view.layer insertSublayer:self.preview atIndex:0];

    // Specify type of barcodes
    self.output.metadataObjectTypes = @[AVMetadataObjectTypeEAN13Code, AVMetadataObjectTypeEAN8Code, AVMetadataObjectTypeUPCECode];
    
    // Start
    [self.session startRunning];
}

- (void)viewDidDisappear:(BOOL)animated {
    [super viewDidDisappear:animated];
    [self.overlayView removeFromSuperview];
    [self.preview removeFromSuperlayer];
    [self stopCapture];
}

#pragma mark - AVCaptureMetadataOutputObjectsDelegate

- (void)captureOutput:(AVCaptureOutput *)captureOutput
didOutputMetadataObjects:(NSArray *)metadataObjects
       fromConnection:(AVCaptureConnection *)connection
{
    
    NSString *upcCode = nil;
    
    for (AVMetadataObject *metadata in metadataObjects)
    {
        if ([metadata.type isEqualToString:AVMetadataObjectTypeEAN13Code])
        {
            upcCode =[(AVMetadataMachineReadableCodeObject *)metadata stringValue];
        }
        else if ([metadata.type isEqualToString:AVMetadataObjectTypeUPCECode])
        {
            upcCode =[(AVMetadataMachineReadableCodeObject *)metadata stringValue];
        }
        else if ([metadata.type isEqualToString:AVMetadataObjectTypeEAN8Code])
        {
            upcCode =[(AVMetadataMachineReadableCodeObject *)metadata stringValue];
        }
    }
    
    if(upcCode){
        [self stopCapture];
        if (self.delegate != nil) {
            [self.delegate UPCScannerController:self didScanResult:upcCode];
        }
    }
}

- (void)cancelled {
    [self stopCapture];
    
    if (self.delegate != nil) {
        [self.delegate UPCScannerControllerDidCancel:self];
    }
}

- (void)showHelp {
    [self stopCapture];
    
    if (self.delegate != nil) {
        [self.delegate UPCScannerControllerShowHelp:self];
    }
}

- (void)stopCapture {
    if(self.session){
        [self.session stopRunning];
        [self.session removeInput:self.input];
        [self.session removeOutput:self.output];
        self.input = nil;
        self.output = nil;
        self.device = nil;
        self.session = nil;
    }
}

- (void)didReceiveMemoryWarning
{
    [self stopCapture];
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

@end
