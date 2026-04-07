static int sum(int a, int b) {
    return a + b;
}
// this function is now visible only inside this .cpp file
// only for this "translation unit"
// so now there will be no duplicate definition in main.cpp