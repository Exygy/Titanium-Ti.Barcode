//
//  UPCScannerController.h
//  barcode
//
//  Created by Pierre Exygy on 9/29/13.
//
//

#import <UIKit/UIKit.h>
#import <AVFoundation/AVFoundation.h>
#import "OverlayView.h"

@protocol UPCScannerDelegate;

@interface UPCScannerController : UIViewController <CancelDelegate, HelpDelegate, AVCaptureMetadataOutputObjectsDelegate>{
    id<UPCScannerDelegate> delegate;
    OverlayView *overlayView;
}

@property (nonatomic, assign) id<UPCScannerDelegate> delegate;

@property (strong, nonatomic) AVCaptureDevice* device;
@property (strong, nonatomic) AVCaptureDeviceInput* input;
@property (strong, nonatomic) AVCaptureMetadataOutput* output;
@property (strong, nonatomic) AVCaptureSession* session;
@property (strong, nonatomic) AVCaptureVideoPreviewLayer* preview;
@property (nonatomic, retain) OverlayView *overlayView;


- (void)captureOutput:(AVCaptureOutput *)captureOutput
didOutputMetadataObjects:(NSArray *)metadataObjects
       fromConnection:(AVCaptureConnection *)connection;

- (id)initWithDelegate:(id<UPCScannerDelegate>)delegate
            showCancel:(BOOL)shouldShowCancel
             showFlash:(BOOL)shouldShowFlash
              showHelp:(BOOL)shouldShowHelp;
@end

@protocol UPCScannerDelegate
- (void)UPCScannerController:(UPCScannerController*)controller didScanResult:(NSString *)result;
- (void)UPCScannerControllerDidCancel:(UPCScannerController*)controller;
- (void)UPCScannerControllerShowHelp:(UPCScannerController*)controller;
@end