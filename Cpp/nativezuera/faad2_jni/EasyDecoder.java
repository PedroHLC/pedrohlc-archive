package faad2;
public class EasyDecoder {
   static {
      System.loadLibrary("faad2_jni");
   }
   
   public native java.lang.String decode(java.lang.String input);
   
   public native boolean init();
   public native int getError();
}