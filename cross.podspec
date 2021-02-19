#
# To learn more about a Podspec see http://guides.cocoapods.org/syntax/podspec.html.
# Run `pod lib lint flutter_plugin.podspec' to validate before publishing.
#
Pod::Spec.new do |s|
  s.name             = 'cross'
  s.version          = '0.0.1'
  s.summary          = 'A cross lib'
  s.description      = <<-DESC
A new Flutter plugin.
                       DESC
  s.homepage         = 'http://example.com'
  s.license          = { :file => '../LICENSE' }
  s.author           = { 'Your Company' => 'email@example.com' }
  s.source           = { :path => '.' }
  s.source_files = 'third_party/jsoncpp/**/*.{cc,cpp,h}','src/**/*.{cc,cpp,h}'
#  s.source_files = 'third_party/jsoncpp/include/**/*.{h}','third_party/jsoncpp/**/*.{cc,cpp}','src/**/*.{h,cc,cpp}'
  s.public_header_files = 'third_party/jsoncpp/include/**/*.h','src/url_signature/include/*.h'
  s.platform = :ios, '8.0'
  s.library = 'c++'
  # 必须配置一下属性，是否会导致项目中找不到头文件
  s.xcconfig = {
        'HEADER_SEARCH_PATHS' => '"${PODS_TARGET_SRCROOT}/third_party/jsoncpp/include/" "${PODS_TARGET_SRCROOT}/src/download/include/" "${PODS_TARGET_SRCROOT}/src/url_signature/include/"'
  }

  # Flutter.framework does not contain a i386 slice.
  s.pod_target_xcconfig = { 'DEFINES_MODULE' => 'YES', 'EXCLUDED_ARCHS[sdk=iphonesimulator*]' => 'i386' }
end
