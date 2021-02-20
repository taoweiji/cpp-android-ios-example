#import "Cross.h"
#include <string>
#include <url_signature.h>

@implementation Cross
- (NSString*)signatureUrl:(NSString *)url{
    std::string str = [url UTF8String];
    std::string result = SignatureUrl(str);
    NSString *newUrl = [NSString stringWithUTF8String:result.c_str()];
    return newUrl;
}
@end
