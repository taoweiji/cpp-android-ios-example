//
//  ViewController.m
//  example
//
//  Created by Wiki on 2021/2/19.
//

#import "ViewController.h"
#import "Cross.h"

@interface ViewController ()

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    NSString* url = @"http://example.com?key2=value2&key3=value3&key1=VALUE1";
    Cross *cross = [[Cross alloc] init];
    NSString*newUrl = [cross signatureUrl:url];
    NSLog(url);
    NSLog(newUrl);
    // Do any additional setup after loading the view.
}
@end
