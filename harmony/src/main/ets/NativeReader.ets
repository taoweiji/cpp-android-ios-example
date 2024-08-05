import testNapi from 'libcross.so';

export class NativeReader {
  add(a: number, b: number): number {
    return testNapi.add(a, b);
  }
  signatureUrl(url: string): string {
    return testNapi.signatureUrl(url);
  }

}