#define MAGIC_NUMBER 'o'

#define operator _IOW(MAGIC_NUMBER,16, int)
#define num1 _IOW(MAGIC_NUMBER,17, int)
#define num2 _IOW(MAGIC_NUMBER,18, int)
#define Read_data _IOR(MAGIC_NUMBER,19, int)
