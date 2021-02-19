#import "Cross.h"
#include <string>
#include <url_signature.h>

@implementation Cross
//+ (void)registerWithRegistrar:(NSObject<FlutterPluginRegistrar>*)registrar {
//  FlutterMethodChannel* channel = [FlutterMethodChannel
//      methodChannelWithName:@"flutter_plugin"
//            binaryMessenger:[registrar messenger]];
//  FlutterPlugin* instance = [[FlutterPlugin alloc] init];
//  [registrar addMethodCallDelegate:instance channel:channel];
//}
//
//- (void)handleMethodCall:(FlutterMethodCall*)call result:(FlutterResult)result {
//  if ([@"getPlatformVersion" isEqualToString:call.method]) {
//    result([@"iOS " stringByAppendingString:[[UIDevice currentDevice] systemVersion]]);
//  } else {
//    result(FlutterMethodNotImplemented);
//  }
//}
- (NSString*)signatureUrl:(NSString *)url{
    std::string str = [url UTF8String];
    std::string result = SignatureUrl(str);
    NSString *newUrl = [NSString stringWithUTF8String:result.c_str()];
    return newUrl;
}

@end
