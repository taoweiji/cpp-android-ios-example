import { NativeReader } from 'harmony'

@Entry
@Component
struct Index {
  @State message: string = 'Hello World';

  build() {
    RelativeContainer() {
      Text('1 + 10 = ' + new NativeReader().add(1, 10))
        .fontSize(12)
        .fontWeight(FontWeight.Bold)
        .alignRules({
          center: { anchor: '__container__', align: VerticalAlign.Center },
          middle: { anchor: '__container__', align: HorizontalAlign.Center }
        })
      Text(new NativeReader().signatureUrl("http://example.com?key2=value2&key3=value3&key1=VALUE1"))
        .fontSize(12)
        .margin({ top: 100 })
        .fontWeight(FontWeight.Bold)
        .alignRules({
          center: { anchor: '__container__', align: VerticalAlign.Center },
          middle: { anchor: '__container__', align: HorizontalAlign.Center }
        })

    }
    .height('100%')
    .width('100%')
  }
}