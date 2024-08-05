Pod::Spec.new do |s|
  s.name             = 'cross'
  s.version          = '0.0.1'
  s.summary          = 'cross library'
  s.description      = 'Cross library'
  s.homepage         = 'http://example.com'
  s.license          = { :file => '../LICENSE' }
  s.author           = { 'Your Company' => 'email@example.com' }
  s.source           = { :path => '.' }
  # 设置源文件，切记不要把测试代码包含进来
  s.source_files = 'platforms/ios/Classes/**/*','third_party/**/*.{cc,cpp,h}','src/**/*.{cc,cpp,h}'
  # 暴露头文件，否则引用该spec的项目无法找到头文件
  s.public_header_files = 'platforms/ios/Classes/**/*.h','src/url_signature/include/*.h'
  s.platform = :ios, '8.0'
  # 必须配置HEADER_SEARCH_PATHS属性，是否会导致项目中C++找不到头文件
  s.xcconfig = {
        'HEADER_SEARCH_PATHS' => '"${PODS_TARGET_SRCROOT}/third_party/cxxurl/include/" "${PODS_TARGET_SRCROOT}/third_party/hash/include/" "${PODS_TARGET_SRCROOT}/src/url_signature/include/"'
  }
end
