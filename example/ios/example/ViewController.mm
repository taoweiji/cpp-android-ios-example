//
//  ViewController.m
//  example
//
//  Created by Wiki on 2021/2/19.
//

#import "ViewController.h"
#include <url_signature.h>

@interface ViewController ()

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    const char* result = UrlSignature("", NULL);
    NSString *str2 = [NSString stringWithUTF8String:result];
    NSLog(str2);
    // Do any additional setup after loading the view.
}


@end
