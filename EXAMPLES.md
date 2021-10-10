# Examples


## Structure With Primitives
```C
typedef struct AllPrimitives {
	char c;
	unsigned char uc;
	byte b;
	short s;
	int i;
	long l;
	float f;
	double d;
} AllPrimitives;
```

### To String
```bash
TO_STRING:
AllPrimitives@55cf7c369030
c: '44';
uc: '255';
b: '0';
s: '1';
i: '2';
l: '3';
f: '4.200000';
d: '5.800000'.
```

### Json Encode
```bash
JSON_ENCODE:
"AllPrimitives@55cf7c369030": {
	"c": 44,
	"uc": 255,
	"b": 0,
	"s": 1,
	"i": 2,
	"l": 3,
	"f": 4.200000,
	"d": 5.800000
}
```

### Json Decode
```bash
JSON_DECODE:
AllPrimitives@55cf7c369110
c: '44';
uc: '255';
b: '0';
s: '1';
i: '2';
l: '3';
f: '4.200000';
d: '5.800000'.
```


## Structure with String Member
```C
typedef struct Parrot {
	char *name;
	int age;
} Parrot;
```

### To String
```bash
TO_STRING:
Parrot@55cf7c3715c0
name: 'Tom';
age: '99'.
```

### Json Encode
```bash
JSON_ENCODE:
"Parrot@55cf7c3715c0": {
	"name": "VG9t",
	"age": 99
}
```

### Json Decode
```bash
JSON_DECODE:
Parrot@55cf7c3715a0
name: 'Tom';
age: '99'.
```


## Structure with Array
```C
typedef struct Array {
	int arr_n;
	int *arr;
} Array;
```

### To String
```bash
TO_STRING:
Array@55cf7c377730
arr_n: '10';
arr: 
'1', '1', '2', '3', '5', '8', '13', '21', '34', '55'.
```

### Json Encode
```bash
JSON_ENCODE:
"Array@55cf7c377730": {
	"arr_n": 10,
	"arr": [1, 1, 2, 3, 5, 8, 13, 21, 34, 55]
}
```

### Json Decode
```bash
JSON_DECODE:
Array@55cf7c3715c0
arr_n: '10';
arr: 
'1', '1', '2', '3', '5', '8', '13', '21', '34', '55'.
```


## Structure with Matrix
```C
typedef struct Matrix3D {
	int matrix_o;
	int matrix_n;
	int matrix_m;
	int ***matrix;
} Matrix3D;
```

### To String
```bash
TO_STRING:
Matrix3D@55cf7c37f990
matrix_o: '2';
matrix_n: '3';
matrix_m: '4';
matrix: 
'0', '-1', '-2', '-3'
'-4', '-5', '-6', '-7'
'-8', '-9', '-10', '-11'

'12', '13', '14', '15'
'16', '17', '18', '19'
'20', '21', '22', '23'.
```

### Json Encode
```bash
JSON_ENCODE:
"Matrix3D@55cf7c37f990": {
	"matrix_o": 2,
	"matrix_n": 3,
	"matrix_m": 4,
	"matrix": [[[0, -1, -2, -3], [-4, -5, -6, -7], [-8, -9, -10, -11]], [[12, 13, 14, 15], [16, 17, 18, 19], [20, 21, 22, 23]]]
}
```

### Json Decode
```bash
JSON_DECODE:
Matrix3D@55cf7c37f9b0
matrix_o: '2';
matrix_n: '3';
matrix_m: '4';
matrix: 
'0', '-1', '-2', '-3'
'-4', '-5', '-6', '-7'
'-8', '-9', '-10', '-11'

'12', '13', '14', '15'
'16', '17', '18', '19'
'20', '21', '22', '23'.
```


## Structure with Matrices
```C
typedef struct Arrays {

	int arr_a;
	int arr_b;
	int **arr;
	
	int brr[2][3][4][5];
	
	int crr_0;
	int crr_1;
	int crr_2;
	int crr[10][10][10];
	
	int drr_2;
	int drr_3;
	int drr_4;
	int*** drr[2][3];
	
	int err_0;
	int err_1;
	int err_2;
	int err_3;
	int ** err[5][5];
} Arrays;
```

###
```bash
TO_STRING:
Arrays@55cf7c385db0
arr_a: '5';
arr_b: '5';
arr: 
'0', '1', '2', '3', '4'
'5', '6', '7', '8', '9'
'10', '11', '12', '13', '14'
'15', '16', '17', '18', '19'
'20', '21', '22', '23', '24';
brr: 
'25', '26', '27', '28', '29'
'30', '31', '32', '33', '34'
'35', '36', '37', '38', '39'
'40', '41', '42', '43', '44'

'45', '46', '47', '48', '49'
'50', '51', '52', '53', '54'
'55', '56', '57', '58', '59'
'60', '61', '62', '63', '64'

'65', '66', '67', '68', '69'
'70', '71', '72', '73', '74'
'75', '76', '77', '78', '79'
'80', '81', '82', '83', '84'


'85', '86', '87', '88', '89'
'90', '91', '92', '93', '94'
'95', '96', '97', '98', '99'
'100', '101', '102', '103', '104'

'105', '106', '107', '108', '109'
'110', '111', '112', '113', '114'
'115', '116', '117', '118', '119'
'120', '121', '122', '123', '124'

'125', '126', '127', '128', '129'
'130', '131', '132', '133', '134'
'135', '136', '137', '138', '139'
'140', '141', '142', '143', '144';
crr_0: '3';
crr_1: '3';
crr_2: '3';
crr: 
'20', '21', '22'
'23', '24', '0'
'1', '2', '3'

'4', '5', '6'
'7', '8', '9'
'10', '11', '12'

'13', '14', '15'
'16', '17', '18'
'19', '20', '21';
drr_2: '4';
drr_3: '4';
drr_4: '4';
drr: 
'22', '23', '24', '0'
'1', '2', '3', '4'
'5', '6', '7', '8'
'9', '10', '11', '12'

'13', '14', '15', '16'
'17', '18', '19', '20'
'21', '22', '23', '24'
'0', '1', '2', '3'

'4', '5', '6', '7'
'8', '9', '10', '11'
'12', '13', '14', '15'
'16', '17', '18', '19'

'20', '21', '22', '23'
'24', '0', '1', '2'
'3', '4', '5', '6'
'7', '8', '9', '10'


'11', '12', '13', '14'
'15', '16', '17', '18'
'19', '20', '21', '22'
'23', '24', '0', '1'

'2', '3', '4', '5'
'6', '7', '8', '9'
'10', '11', '12', '13'
'14', '15', '16', '17'

'18', '19', '20', '21'
'22', '23', '24', '0'
'1', '2', '3', '4'
'5', '6', '7', '8'

'9', '10', '11', '12'
'13', '14', '15', '16'
'17', '18', '19', '20'
'21', '22', '23', '24'


'0', '1', '2', '3'
'4', '5', '6', '7'
'8', '9', '10', '11'
'12', '13', '14', '15'

'16', '17', '18', '19'
'20', '21', '22', '23'
'24', '0', '1', '2'
'3', '4', '5', '6'

'7', '8', '9', '10'
'11', '12', '13', '14'
'15', '16', '17', '18'
'19', '20', '21', '22'

'23', '24', '0', '1'
'2', '3', '4', '5'
'6', '7', '8', '9'
'10', '11', '12', '13'



'14', '15', '16', '17'
'18', '19', '20', '21'
'22', '23', '24', '0'
'1', '2', '3', '4'

'5', '6', '7', '8'
'9', '10', '11', '12'
'13', '14', '15', '16'
'17', '18', '19', '20'

'21', '22', '23', '24'
'0', '1', '2', '3'
'4', '5', '6', '7'
'8', '9', '10', '11'

'12', '13', '14', '15'
'16', '17', '18', '19'
'20', '21', '22', '23'
'24', '0', '1', '2'


'3', '4', '5', '6'
'7', '8', '9', '10'
'11', '12', '13', '14'
'15', '16', '17', '18'

'19', '20', '21', '22'
'23', '24', '0', '1'
'2', '3', '4', '5'
'6', '7', '8', '9'

'10', '11', '12', '13'
'14', '15', '16', '17'
'18', '19', '20', '21'
'22', '23', '24', '0'

'1', '2', '3', '4'
'5', '6', '7', '8'
'9', '10', '11', '12'
'13', '14', '15', '16'


'17', '18', '19', '20'
'21', '22', '23', '24'
'0', '1', '2', '3'
'4', '5', '6', '7'

'8', '9', '10', '11'
'12', '13', '14', '15'
'16', '17', '18', '19'
'20', '21', '22', '23'

'24', '0', '1', '2'
'3', '4', '5', '6'
'7', '8', '9', '10'
'11', '12', '13', '14'

'15', '16', '17', '18'
'19', '20', '21', '22'
'23', '24', '0', '1'
'2', '3', '4', '5';
err_0: '2';
err_1: '2';
err_2: '2';
err_3: '2';
err: 
'1', '2'
'3', '4'

'5', '6'
'7', '8'


'9', '10'
'11', '12'

'13', '14'
'0', '1'.
```

### Json Encode
```bash
JSON_ENCODE:
"Arrays@55cf7c385db0": {
	"arr_a": 5,
	"arr_b": 5,
	"arr": [[0, 1, 2, 3, 4], [5, 6, 7, 8, 9], [10, 11, 12, 13, 14], [15, 16, 17, 18, 19], [20, 21, 22, 23, 24]],
	"brr": [[[[25, 26, 27, 28, 29], [30, 31, 32, 33, 34], [35, 36, 37, 38, 39], [40, 41, 42, 43, 44]], [[45, 46, 47, 48, 49], [50, 51, 52, 53, 54], [55, 56, 57, 58, 59], [60, 61, 62, 63, 64]], [[65, 66, 67, 68, 69], [70, 71, 72, 73, 74], [75, 76, 77, 78, 79], [80, 81, 82, 83, 84]]], [[[85, 86, 87, 88, 89], [90, 91, 92, 93, 94], [95, 96, 97, 98, 99], [100, 101, 102, 103, 104]], [[105, 106, 107, 108, 109], [110, 111, 112, 113, 114], [115, 116, 117, 118, 119], [120, 121, 122, 123, 124]], [[125, 126, 127, 128, 129], [130, 131, 132, 133, 134], [135, 136, 137, 138, 139], [140, 141, 142, 143, 144]]]],
	"crr_0": 3,
	"crr_1": 3,
	"crr_2": 3,
	"crr": [[[20, 21, 22], [23, 24, 0], [1, 2, 3]], [[4, 5, 6], [7, 8, 9], [10, 11, 12]], [[13, 14, 15], [16, 17, 18], [19, 20, 21]]],
	"drr_2": 4,
	"drr_3": 4,
	"drr_4": 4,
	"drr": [[[[[22, 23, 24, 0], [1, 2, 3, 4], [5, 6, 7, 8], [9, 10, 11, 12]], [[13, 14, 15, 16], [17, 18, 19, 20], [21, 22, 23, 24], [0, 1, 2, 3]], [[4, 5, 6, 7], [8, 9, 10, 11], [12, 13, 14, 15], [16, 17, 18, 19]], [[20, 21, 22, 23], [24, 0, 1, 2], [3, 4, 5, 6], [7, 8, 9, 10]]], [[[11, 12, 13, 14], [15, 16, 17, 18], [19, 20, 21, 22], [23, 24, 0, 1]], [[2, 3, 4, 5], [6, 7, 8, 9], [10, 11, 12, 13], [14, 15, 16, 17]], [[18, 19, 20, 21], [22, 23, 24, 0], [1, 2, 3, 4], [5, 6, 7, 8]], [[9, 10, 11, 12], [13, 14, 15, 16], [17, 18, 19, 20], [21, 22, 23, 24]]], [[[0, 1, 2, 3], [4, 5, 6, 7], [8, 9, 10, 11], [12, 13, 14, 15]], [[16, 17, 18, 19], [20, 21, 22, 23], [24, 0, 1, 2], [3, 4, 5, 6]], [[7, 8, 9, 10], [11, 12, 13, 14], [15, 16, 17, 18], [19, 20, 21, 22]], [[23, 24, 0, 1], [2, 3, 4, 5], [6, 7, 8, 9], [10, 11, 12, 13]]]], [[[[14, 15, 16, 17], [18, 19, 20, 21], [22, 23, 24, 0], [1, 2, 3, 4]], [[5, 6, 7, 8], [9, 10, 11, 12], [13, 14, 15, 16], [17, 18, 19, 20]], [[21, 22, 23, 24], [0, 1, 2, 3], [4, 5, 6, 7], [8, 9, 10, 11]], [[12, 13, 14, 15], [16, 17, 18, 19], [20, 21, 22, 23], [24, 0, 1, 2]]], [[[3, 4, 5, 6], [7, 8, 9, 10], [11, 12, 13, 14], [15, 16, 17, 18]], [[19, 20, 21, 22], [23, 24, 0, 1], [2, 3, 4, 5], [6, 7, 8, 9]], [[10, 11, 12, 13], [14, 15, 16, 17], [18, 19, 20, 21], [22, 23, 24, 0]], [[1, 2, 3, 4], [5, 6, 7, 8], [9, 10, 11, 12], [13, 14, 15, 16]]], [[[17, 18, 19, 20], [21, 22, 23, 24], [0, 1, 2, 3], [4, 5, 6, 7]], [[8, 9, 10, 11], [12, 13, 14, 15], [16, 17, 18, 19], [20, 21, 22, 23]], [[24, 0, 1, 2], [3, 4, 5, 6], [7, 8, 9, 10], [11, 12, 13, 14]], [[15, 16, 17, 18], [19, 20, 21, 22], [23, 24, 0, 1], [2, 3, 4, 5]]]]],
	"err_0": 2,
	"err_1": 2,
	"err_2": 2,
	"err_3": 2,
	"err": [[[[1, 2], [3, 4]], [[5, 6], [7, 8]]], [[[9, 10], [11, 12]], [[13, 14], [0, 1]]]]
}
```

### Json Decode
```bash
JSON_DECODE:
Arrays@55cf7c3888b0
arr_a: '5';
arr_b: '5';
arr: 
'0', '1', '2', '3', '4'
'5', '6', '7', '8', '9'
'10', '11', '12', '13', '14'
'15', '16', '17', '18', '19'
'20', '21', '22', '23', '24';
brr: 
'25', '26', '27', '28', '29'
'30', '31', '32', '33', '34'
'35', '36', '37', '38', '39'
'40', '41', '42', '43', '44'

'45', '46', '47', '48', '49'
'50', '51', '52', '53', '54'
'55', '56', '57', '58', '59'
'60', '61', '62', '63', '64'

'65', '66', '67', '68', '69'
'70', '71', '72', '73', '74'
'75', '76', '77', '78', '79'
'80', '81', '82', '83', '84'


'85', '86', '87', '88', '89'
'90', '91', '92', '93', '94'
'95', '96', '97', '98', '99'
'100', '101', '102', '103', '104'

'105', '106', '107', '108', '109'
'110', '111', '112', '113', '114'
'115', '116', '117', '118', '119'
'120', '121', '122', '123', '124'

'125', '126', '127', '128', '129'
'130', '131', '132', '133', '134'
'135', '136', '137', '138', '139'
'140', '141', '142', '143', '144';
crr_0: '3';
crr_1: '3';
crr_2: '3';
crr: 
'20', '21', '22'
'23', '24', '0'
'1', '2', '3'

'4', '5', '6'
'7', '8', '9'
'10', '11', '12'

'13', '14', '15'
'16', '17', '18'
'19', '20', '21';
drr_2: '4';
drr_3: '4';
drr_4: '4';
drr: 
'22', '23', '24', '0'
'1', '2', '3', '4'
'5', '6', '7', '8'
'9', '10', '11', '12'

'13', '14', '15', '16'
'17', '18', '19', '20'
'21', '22', '23', '24'
'0', '1', '2', '3'

'4', '5', '6', '7'
'8', '9', '10', '11'
'12', '13', '14', '15'
'16', '17', '18', '19'

'20', '21', '22', '23'
'24', '0', '1', '2'
'3', '4', '5', '6'
'7', '8', '9', '10'


'11', '12', '13', '14'
'15', '16', '17', '18'
'19', '20', '21', '22'
'23', '24', '0', '1'

'2', '3', '4', '5'
'6', '7', '8', '9'
'10', '11', '12', '13'
'14', '15', '16', '17'

'18', '19', '20', '21'
'22', '23', '24', '0'
'1', '2', '3', '4'
'5', '6', '7', '8'

'9', '10', '11', '12'
'13', '14', '15', '16'
'17', '18', '19', '20'
'21', '22', '23', '24'


'0', '1', '2', '3'
'4', '5', '6', '7'
'8', '9', '10', '11'
'12', '13', '14', '15'

'16', '17', '18', '19'
'20', '21', '22', '23'
'24', '0', '1', '2'
'3', '4', '5', '6'

'7', '8', '9', '10'
'11', '12', '13', '14'
'15', '16', '17', '18'
'19', '20', '21', '22'

'23', '24', '0', '1'
'2', '3', '4', '5'
'6', '7', '8', '9'
'10', '11', '12', '13'



'14', '15', '16', '17'
'18', '19', '20', '21'
'22', '23', '24', '0'
'1', '2', '3', '4'

'5', '6', '7', '8'
'9', '10', '11', '12'
'13', '14', '15', '16'
'17', '18', '19', '20'

'21', '22', '23', '24'
'0', '1', '2', '3'
'4', '5', '6', '7'
'8', '9', '10', '11'

'12', '13', '14', '15'
'16', '17', '18', '19'
'20', '21', '22', '23'
'24', '0', '1', '2'


'3', '4', '5', '6'
'7', '8', '9', '10'
'11', '12', '13', '14'
'15', '16', '17', '18'

'19', '20', '21', '22'
'23', '24', '0', '1'
'2', '3', '4', '5'
'6', '7', '8', '9'

'10', '11', '12', '13'
'14', '15', '16', '17'
'18', '19', '20', '21'
'22', '23', '24', '0'

'1', '2', '3', '4'
'5', '6', '7', '8'
'9', '10', '11', '12'
'13', '14', '15', '16'


'17', '18', '19', '20'
'21', '22', '23', '24'
'0', '1', '2', '3'
'4', '5', '6', '7'

'8', '9', '10', '11'
'12', '13', '14', '15'
'16', '17', '18', '19'
'20', '21', '22', '23'

'24', '0', '1', '2'
'3', '4', '5', '6'
'7', '8', '9', '10'
'11', '12', '13', '14'

'15', '16', '17', '18'
'19', '20', '21', '22'
'23', '24', '0', '1'
'2', '3', '4', '5';
err_0: '2';
err_1: '2';
err_2: '2';
err_3: '2';
err: 
'1', '2'
'3', '4'

'5', '6'
'7', '8'


'9', '10'
'11', '12'

'13', '14'
'0', '1'.
```


## Structure with Matrices of Strings
```C
typedef struct Strings {
	
	int stra_0;
	int stra_1;
	char ***stra;
	
	char strb[5][5][32];
	
	int strc_0;
	int strc_1;
	char strc[4][4][10];
	
	int strd_2;
	int strd_3;
	char*** strd[6][6];
	
	int stre_0;
	int stre_1;
	int stre_2;
	int stre_3;
	char***stre[7][7];
} Strings;
```

### To String
```bash
TO_STRING:
Strings@55cf7c36a790
stra_0: '5';
stra_1: '5';
stra: 
'Q48aFE', 'oKNtL', 'MQNN5E', 'vtBl33aPMI', 'QOkKc'
'2DZMBSnCs', 'Kg83Zs1', 's1T2Mdgm', 'FgbHhpI', 'ulC9A'
'18x31G1a', '1Bw1ivbppV', '8a5GU', 'umjBVj3kj1', 'kaskyz'
'cMBSuKbd', 'W8DZsdopi', 'pI6aXvEu', 'KUasRy4Z6', 'yrwdN4TspV'
'Byu4c8m9s', 'B1FuT2pb6Z', 'o33u6Ubg', '6dFpfpjXg', 'gaP9n';
strb: 
'39', '59', '4a', '59', '54', '37', '64', '57', '4b', '51', '44', '55', '75', '6e', '33', '75', '50', '4a', '45', '39', '78', '37', '72', '62', '56', '6f', '6c', '49', '70', '36', '41', '52'
'76', '53', '54', '53', '35', '6e', '4e', '36', '58', '4c', '5a', '46', '46', '68', '6c', '6b', '35', '63', '72', '6a', '43', '54', '4a', '61', '4e', '4a', '74', '50', '66', '77', '68', '62'
'76', '70', '36', '6e', '56', '6a', '50', '6f', '66', '47', '4e', '38', '4b', '42', '6b', '7a', '54', '70', '31', '6e', '55', '55', '73', '73', '57', '6a', '77', '7a', '57', '34', '43', '6e'
'50', '6f', '6a', '73', '6e', '63', '36', '6e', '6f', '6b', '78', '59', '49', '61', '46', '7a', '6b', '63', '71', '72', '57', '6c', '38', '4f', '6e', '6b', '6d', '65', '6b', '4d', '73', '43'
'33', '4d', '7a', '68', '58', '57', '76', '52', '34', '4f', '79', '6b', '6f', '4c', '47', '7a', '6a', '59', '75', '43', '4e', '50', '64', '59', '37', '75', '58', '52', '58', '7a', '4f', '56'

'76', '36', '50', '36', '6f', '34', '4d', '7a', '59', '6e', '56', '74', '43', '36', '65', '66', '73', '73', '76', '78', '36', '52', '31', '46', '4c', '73', '5a', '58', '41', '54', '56', '71'
'48', '39', '6f', '6a', '73', '36', '34', '73', '43', '43', '41', '59', '46', '32', '32', '71', '39', '4f', '51', '76', '59', '37', '67', '58', '45', '31', '77', '77', '4b', '77', '4a', '66'
'32', '76', '58', '42', '58', '75', '46', '67', '43', '56', '42', '34', '64', '37', '37', '6d', '57', '4c', '39', '72', '63', '51', '37', '7a', '6d', '38', '5a', '33', '6e', '56', '70', '64'
'48', '7a', '37', '48', '4d', '6c', '33', '59', '66', '66', '4f', '47', '33', '5a', '53', '55', '37', '44', '48', '4c', '66', '58', '50', '69', '58', '32', '79', '4a', '7a', '6a', '77', '67'
'66', '55', '42', '42', '78', '54', '39', '74', '64', '79', '47', '73', '46', '62', '69', '6c', '55', '6d', '37', '50', '69', '56', '67', '6b', '76', '51', '54', '6b', '32', '35', '6b', '48'

'32', '51', '48', '32', '76', '57', '6f', '44', '61', '37', '6b', '58', '55', '32', '43', '4b', '45', '6f', '46', '58', '39', '62', '71', '78', '41', '67', '4b', '49', '48', '4e', '46', '65'
'6b', '74', '43', '42', '39', '69', '49', '50', '54', '49', '61', '52', '4d', '74', '34', '64', '6d', '51', '56', '74', '4d', '4d', '46', '79', '6d', '62', '73', '4a', '54', '67', '58', '44'
'38', '4d', '38', '72', '4b', '4f', '6e', '41', '55', '49', '58', '78', '39', '63', '63', '6b', '61', '78', '57', '39', '7a', '45', '6f', '52', '53', '43', '67', '73', '4c', '64', '4b', '6c'
'77', '72', '38', '67', '53', '47', '35', '56', '54', '41', '6b', '4c', '49', '36', '4a', '35', '32', '4a', '61', '48', '72', '78', '4a', '56', '6b', '70', '6d', '35', '45', '59', '69', '74'
'6d', '36', '69', '67', '4b', '63', '44', '5a', '4c', '45', '4b', '48', '32', '4e', '53', '50', '51', '54', '55', '64', '70', '5a', '4a', '47', '69', '36', '64', '52', '46', '75', '43', '56'

'65', '6a', '46', '4a', '42', '63', '61', '6b', '34', '74', '36', '74', '4f', '4c', '4a', '73', '6c', '52', '6d', '58', '5a', '76', '46', '76', '39', '66', '53', '79', '4f', '32', '4e', '39'
'33', '4f', '65', '4b', '39', '76', '64', '56', '4d', '69', '73', '43', '48', '6d', '73', '4a', '6b', '74', '45', '51', '4d', '52', '67', '35', '6f', '62', '7a', '69', '47', '76', '42', '50'
'79', '34', '68', '6c', '34', '61', '6a', '62', '64', '69', '37', '74', '61', '79', '34', '67', '76', '46', '6a', '74', '38', '39', '75', '78', '74', '53', '64', '72', '4f', '6e', '48', '34'
'73', '43', '67', '69', '4b', '59', '63', '4f', '67', '38', '50', '6a', '31', '37', '75', '47', '52', '42', '4e', '4c', '6f', '5a', '31', '71', '4e', '64', '69', '6f', '39', '76', '55', '34'
'61', '46', '67', '43', '46', '59', '47', '70', '33', '77', '66', '59', '51', '78', '72', '4a', '66', '34', '35', '4d', '79', '44', '34', '56', '37', '4d', '48', '77', '5a', '41', '38', '64'

'6d', '5a', '41', '54', '6a', '6b', '45', '6c', '65', '48', '50', '7a', '56', '34', '4f', '6f', '6a', '57', '74', '53', '4d', '67', '74', '7a', '66', '4c', '33', '68', '53', '69', '78', '46'
'56', '54', '64', '63', '71', '31', '31', '4d', '77', '59', '57', '73', '32', '4d', '4b', '6e', '74', '4b', '39', '55', '6c', '45', '49', '55', '33', '31', '76', '68', '47', '41', '76', '41'
'36', '67', '50', '38', '38', '6a', '4e', '35', '59', '75', '4f', '39', '43', '6f', '52', '33', '4a', '77', '64', '6e', '34', '56', '5a', '54', '42', '55', '36', '7a', '6a', '77', '63', '4f'
'70', '67', '4e', '67', '70', '78', '50', '77', '77', '77', '38', '75', '31', '55', '36', '42', '50', '4f', '38', '6f', '43', '72', '7a', '57', '78', '37', '56', '34', '4e', '64', '53', '69'
'4b', '33', '63', '35', '51', '55', '33', '45', '6c', '59', '73', '42', '75', '6f', '67', '4d', '58', '77', '4b', '6f', '58', '6d', '52', '44', '4d', '38', '45', '39', '79', '73', '50', '75';
strc_0: '3';
strc_1: '3';
strc: 
'MxLrgR68e', 'feIjq', 'lKtfVBPe4'
'Y86dh3H', 'uyZsa4U', 'yg5fCxt8'
'85Qp7w', 'tyiWi6KzoOQSxiNJpsP', 'QSxiNJpsP';
strd_2: '4';
strd_3: '4';
strd: 
'cJREZeX', 'fHwQ6SG9', 'pjd5N5v', '3sxs5oHLL'
'S5aOj7ZN', 'EApu3U', '5TQWK', 'ZaCBQS'
'zrmbviCQq', 'ASW3NEOx', 's4uqT', 'zb52pLxzlM'
'OXbHSondac', 'MBRp1KhENL', '3LlCf', 'dsJ2rgGV'

'soCHyL', 'HwPTQfEjvY', 'VnRGK', 'TJ81E2TVib'
'lhcpnrX7n', 'v3wFBOgSba', 'gggMj1ZUbR', 'X7hlaanH'
'6LNJF', 'ynecC', 'ZocouhN', '16Y8l8gST'
'nI6vbLePgf', 'pZ6bggFSa', 'AgwKJitmXj', 'WxT7sFHP'

'2M17vg', 'a9DHLw', 'INeXv6aW', 'FtA81bG'
'nFwYsb9WT', 'gx2sw1', '3xWd6t', 'aVyaz1k'
'GQY98SIPT', 'rTjfTCg7x', 'eUGxE', 'G42u4FHOZ'
'lQE5TG', '3wsVbjjuE', '25U3L', '27FDZ'

'YDXuhNL', 'YXfMJK', 'u7Na631', 'CO5MzJLBcR'
'P3GWtz', 'blsgGblD', 'vHGWO', 'UINvbC1wS'
'wmpf3PKl2i', 'nU2hrJeD', 'UltTVSb', 'ZpW3HKf'
'WtpEkbe9nn', 'hI5CgxqMh', 'baPFC', 'RA6xdaAVAo'

'JJRqtse9', 'UoY4q', 'fZ1uEWN', '6aMGt'
'6pnZCY7y', 'uLlxbcEOJ', 'U66o2Ssd', '9nlrH16'
'RrVkhGX', 'shc3uNUa3B', 'FuRngwNnM', 'RImFENrgL'
'OimOzngAQ', '4dmTKCGHzS', '5kpL2u', 'h899d'

'GFytbDxn6', 'tBVMAgPxlw', 'se2fn8z', 'jectgUP'
'worrxq7xXx', 'gXd9rx9n3t', 'IRwwKcGQEN', 'H9sNuDJI'
'rWpdFAkaDT', 'kokW7B', 'TbfxflGa', 'n8fcsBSROc'
'1uUoYCU', '3WEUqV9', 'gXD5lL', 'BrfOF3e'


'1hbo5lVilb', '8UGu9', 'wLuEAYnVMy', '1gn1S4'
'Fxr4XPV', 'gAuxCgfw', '8Gz2SOPS5u', 'Ho3ESrY'
'ZWRosLSut7', 'wtwErCsCI', 'qztjzHqRl', 'v5hDfucmj'
'BmD8eM4z', 'OK2q3kEHn', 'odPaOzYV', 'usnrZd'

'5pabw2frw', 'WAewBzz', 'Aq9j4', 'YgRHoV6syg'
'hhwmmv9o', 'iyqPZZKMo', '5XpIO', 'TFJJwYu'
'HD8sCf', 'eWqZl', 'AkpEcwZwL', 'DTuRGLJd'
'Rj1vF1Y', 'qnG8ith', 'OnAJjqR5', 'yJy3rXYQL'

'gLHPMdc8EO', 'zg3tuzsJc', '3fX5v', 'O7IKlQ'
'qb1YTQdq4', 'qyBQn', '7yFj9KVCb1', 'gle2EU'
'udmQlQsWDu', 'p1ixF', 'RRQv9Qqc4', 'cRMxL'
'3lOQS', 'dNzRMI', 'AgPdCux', 'gMbRlwQC3'

'BlnceJJ', 'alq2nKf', 'tpxIGKTaz8', '41zXBZlj'
'iutQYsmt', 'ClfeV4', 'DUiuSPiS', '9U5m58Has'
'NTVeFLWw2n', 'MsKubQBSd8', 'Mqz5i', 'gQUsrEz'
'l69xR', 'zCqUjPRe', 'S63Xv7eFlP', 'DX4uLxpN'

'ZuhDg4r7I', 'qlkqsVy', 'PUerj6tR', 'IVZRH91Ec5'
'WS9OenH', 'x4BtI9g8', 'nS7iIM', 'x6L7QXZqR2'
'GmYo2Uyy', 'fmcb9yRgC', 'tjU6xiBgg', 'gtfXJTVbJ'
'CtOgOJRfr', 'VhXEzhK', 'AtM6gd1uB', 'DG5YMA4IQ'

'2AeN96nWx', 'MtnNpBppru', 'V4oW32EOQ', 'PslYjb'
'21bMt', 'Cc4tG', 'zNqxuA', 'uftFWV'
'4QvmDcmaxD', 'gujW2R31Dc', 'x1lHtt', '8alYH2k'
'QPFs9eb', 'AmwSbCiA', 'ierkgWvY4r', '5WFEs'


'XkPkNzN7r', '2lrhUgW6Pr', 'huDZodT', 'UrS6Ce2g'
'8mWq3FnU9q', 'Ksfym77', 'kAO6Bl9L', 'qtOoFojF'
'Vzw6t', 'gbiBRsD', '6l93LuLzg5', 'YKz4EvM4U'
'oUjGCg', 'u8zsn', 'sjGeXtu7', '5bXT4ZI'

'VVggPaOqm', 'EKfqr', 'VdUqn', 'BEpKi'
'PC2YLj1W', 'PAics9', 'kpRgRpxe1l', 'iaMn1X'
'UDMTgId6', 'Jg4IHaar', 'mI6mqGGjF', 'kUC6lZPGn'
'KzZubW5JLi', 'kCGN3WDzf7', '31BzZ', 'ukI7Xmah9'

'y1QBhc', 'gnf9MIrKPr', 'r6ghx', 'vgRFD'
'q1SPBwyI', 'A2WPOGnj', 'sQ5P1nFxZ', 'oUqjTXq'
'3fub7yq', 'CCgdCIC', 'gCxqhg', 'Y2U6UQty'
'mk8RYyk', 'qJZ4cH1', 'Ox17JbSKtG', 'S2Pdn9'

'rDRWfDkiF', '4DSSySK', 'pQVzhkygq', 'CoN82W'
'gd9E81Y', 'Dg6biwGG7o', 'cxETMbXC', 'CvpoJgK'
'hvDqZK', '82xC6Dqmy', 'ety6qGMR', 'ykz7fJQ9M'
'NRnB9x4L', 'E5sFonKgsG', 'g1kH5GY', 'XE5JyR'

'f8HrOhy1w', 'v2LJFXyDd5', '8Iz1pvJ', 'qEJyk3VJi'
'2Pj1WiD', 'xnFvfX', 'JLxfI', 'zaJISJWm5'
'QFCmge', 'JRZRwtvf', 'fGd4GGgE', '7l7YvW'
'oxFTY9zaM', 'krQSyBm', '1gfdMHkhV8', 'cdr19HRypV'

'fdgB7m', 'YqL1z', 'BpRfrOu', '2jUquod'
'rnKbXDEzTu', 'ci4Iefpvn', 'Py3qLwfwcK', '3IZVz'
'h7P1WB4p', 'hQEVm', 'wEz4AJtuY', 'ofgtGLWXWW'
'nEST1auV', 'm5z38t', 'plvHO', 'yZU5xnY'


'4eTDFT71nM', 'EjEORlN4', 'DPKNRc3', '5Iq6JF'
'WkNEBCebd', 'tVirByNI4X', 'bVhWWnTka', '3OxTYgGeU'
'gEHQQ3', 'u4jmQsV', 'CzGsDsgcFM', 'wSaKd'
'kwiMw', 'yyqSGxONge', 'OC54gK1b1', 'GH8xiuS'

'jxlERyg6X', 'z47eN', 'rg1rL1', 'TH4q5'
'LpIfAoBVY4', '1vZ5YJt', 'ey22rNY1', 'D5pTsB'
'5yX2L', 'HLkIX5', '9ZOsXIvL', 'xXqvwSJ7O'
'sEXwbI1NgC', 'Z4ZmgFiKU', 'snAJUzIDqE', 'Sxuiei'

'nerkr', '2bZufb', 'U6QbS3y', 'eGWBiJeh5'
'BtQghUf', 'mWo7l', 'q1lL3TgyjM', 'UGs7LO27ag'
'MAgvsRQDnI', 'MmHRV25', 'wOIlGQeJTl', '6kCzC'
'5cMWrSQPne', 'mtmIVy9ODa', 'jPPv9TB', 'K1vJWOWeh9'

'4YnQdxGzr', 'APMzlzW5kE', 'k9S1Gs', 'tlcy94GkbW'
'OrEkq6KRT', '3iJkgWkrCQ', 'f6El8jZE', 'FsegPalQ'
'5cVsddUXA', 'JsuwgKE', 'ic6uihk', 'qO4PE8tnkv'
'8kWBuZ', 'hi12PixDz', 'eLdpQ', '3rctO'

'PmMwwXg', '5Ai3SB', 'tPABXEptt', 'tg8g7M8YN'
'GJRHZ', '4C81rdP', 'iEvbFPe16', 'gepzGuPE6d'
'VIzLG', '58eNg', 'xCQr5QogVl', 'jiZ8KVluZ'
'OPVwF4', 'ShqtpAhgp', 'Ot7fWdt', 'r9qkM'

'8Orpz', 'TrWFhLcHu', 'zCMQpQCzi', 'WgxQTW'
'GZP1cCE', 'axD9In', 'QcqJ63', 's8ZIW'
'aeO95', '7ndOHTwmA', '7sjWzi', 'vnMWlTeXNf'
'5g3wVfK', '1MaSHh4t1v', 'Y11EQj', 'Sst8XucC'


'loieuyxN4K', 'yLvYcx', '754dHdvV', 'SjqwJ'
'hMRRlQT', 'WJe6zYQ8', 'T97llQfUdD', 'zQeJQGk3'
'4dNZc2g', 'WlZyn', 'U1b1UJSzad', 'wZkWCFYuP'
'OSKGs', 'IvJEwJ', 'ecBVVioWgq', 'N3SWoz8Br'

'Svyj251eZ8', 'f5ppa', 'KYIKR', 'WrM5pX'
'uTOz3', 'v4Cg9oPe', '2l7Z8', 'OPloChatsb'
'ViXNMjM', 'F9wxaOc', 'DfJb4mBszg', 'UYq8Wh2'
'ghbowRkT', '88RZx', 'gcMfFlIh', 'smtCV'

'jamCmPnNg', '7c4BBzf', 'lUtXdR1Yw', 'n7fVj'
'LBRgC', 'HMxJBhao', 'PC5RiY', 'ZHGkV'
'ds5tu', 'QwIhwqt', 'ncfgyohJ', '6ljLyHDsw5'
'fa4VxAaEKx', 'hM4Arsq1', 'rlu6T3HN', 'Xdxtf'

'Y7IoCrN', 'q23ddwd', 'sSggg', 'tsv8R1p1'
'N57u1pyplt', 'Smz6IFG4', 'rjgvVz8BS8', 'PrjBrPelq'
'SXZyBW1', 'TeN3blM1m', 'SYyzK', 'j2dmkxC'
'gHhsgg', '3v154j22N', 'FR8ylD', 'k6eLQ'

'4CZktoD', 'oaisfIdgY', 'qpsdO5', 'qw9MOr'
'R7lGdy5Wcd', 'L1yyRzgZDU', 'JRA1SI', 'COa297dgw'
'LzHOk4V5c', 'BoBn8ni9', 'NGuT7yFr', '9skNDiItsW'
'FKu5DDed1', 'EN5HWw3g', 'mvTMx', 'uqEbSXsQ8'

'fKvYLFpGH', 'hB8SoY', 'XTDpKZXg', 'DIrL5'
'PQrmdxfq', 'P7YcfpDyX', 'vDjkq3eGu', 'JDSgNpOk'
'KMgCEZu', 'RzHw1m', 'hUQQzHEam', 'OnYgMptN'
'9QbfzwHos', 'JLrbkS', 'ygoGO', 'fddaRnuo'


'FD2oBJnuTf', 'GKbmHSX', 'mQ5ZXgwc', 'gFmebQj'
'hVA4pJH', 'dgM7u', 'TJqcA', 'Uuk212'
'nmE1N', 'OMHnHBK', 'VNhMQu9', 'BWPe3Se2'
'ImvOb3jbKB', 'GGxPAZOs8', 'g5g6uhJ', 'hD5NpA'

'peNw7pVL', 'RWTaCS6oF', 'g4JtjtB', 'qtuEvgW'
'lKQsErC', 'cHMm7', '2zFHYe3QU', 'GZGpog'
'Irx2G', 'C3wO2PG', 'OibnZ', 'QzgAuivb'
'Zzr6Ne', 'E7XDGXz', 'TrHqOOLp', 'u1hzvVNgg9'

'ssaVge', 'e4wDIs', 'K3oIajCoHg', 'Ade9zEl'
'Zgw64d9y6G', 'TRbCsGa', '6qQKZC', '2fRk9bHi'
'ZWO6Uvm', 'q5tlL', 'YVRuFx9Jz', 'xXmMOHWmja'
'5GegCimg7', '23IiGegT', 'J7mh6oyT', 'EVjUA'

'3YJW2', 'T3Bdi', 'bWgwklIGcB', 'wSE5r'
'GGpkTKj', 'vlcHIyfpE', 'O5rxm', 'cIX8S7fmLT'
'xxh41JvFcS', 'SgEkhGV', 'BkUJv', 'VLBFcVoM'
'pB8HAQnJfC', 'FpoIyt', 'X4RpBcuAN', '3ClsJn8W9Y'

'xnLiJw', '6d5BgI', 'dwx7qR75', 'jCTnxDtZu'
'AzQXgYt', 'RWqJXpd1k', '7z3cf', '4GhyUTN'
'6mszy', 'VH74U1dM', 'AB4rNn', 'Emd2G2RAk'
'aPrvy', 'asqMpzVot', 'agJKXlh', 'lei4CIDt'

'VPE31Xe', 'rEXlG', 'SeEQ64B', 'z9nv5tpuW'
'VtyV8gXp1', 'ODmkNr22tB', 'U6Lw87k', 'IRpZLtNy8'
'rXVMxgC', 'gVKsych8Y', 'e7KJA9PQ', 'UDlXNdKC'
'yJzmSsZMFo', 'lDumW5oPS', '3kWzfmGtcW', 'a5M5fJ';
stre_0: '2';
stre_1: '2';
stre_2: '2';
stre_3: '2';
stre: 
'q65WK', '9kfg98rem'
'ECgj7J2c84', 'rharvgi'

'ynrRXmS1DX', 'mvlXXvAZ2L'
'l3aPrF8', 'ZaM6X'


'TUKjnjN4JL', 'fWHfkS'
'k4bRJE4IX', 'DGXhlSF'

'wS3NTBduDY', 'vz6bNOgQP'
'xDHoTrPh', 'ObSOv'.
```

### Json Encode
```bash
JSON_ENCODE:
"Strings@55cf7c36a790": {
	"stra_0": 5,
	"stra_1": 5,
	"stra": [["UTQ4YUZF", "b0tOdEw=", "TVFOTjVF", "dnRCbDMzYVBNSQ==", "UU9rS2M="], ["MkRaTUJTbkNz", "S2c4M1pzMQ==", "czFUMk1kZ20=", "RmdiSGhwSQ==", "dWxDOUE="], ["MTh4MzFHMWE=", "MUJ3MWl2YnBwVg==", "OGE1R1U=", "dW1qQlZqM2tqMQ==", "a2Fza3l6"], ["Y01CU3VLYmQ=", "VzhEWnNkb3Bp", "cEk2YVh2RXU=", "S1Vhc1J5NFo2", "eXJ3ZE40VHNwVg=="], ["Qnl1NGM4bTlz", "QjFGdVQycGI2Wg==", "bzMzdTZVYmc=", "NmRGcGZwalhn", "Z2FQOW4="]],
	"strb": [[[39, 59, 4a, 59, 54, 37, 64, 57, 4b, 51, 44, 55, 75, 6e, 33, 75, 50, 4a, 45, 39, 78, 37, 72, 62, 56, 6f, 6c, 49, 70, 36, 41, 52], [76, 53, 54, 53, 35, 6e, 4e, 36, 58, 4c, 5a, 46, 46, 68, 6c, 6b, 35, 63, 72, 6a, 43, 54, 4a, 61, 4e, 4a, 74, 50, 66, 77, 68, 62], [76, 70, 36, 6e, 56, 6a, 50, 6f, 66, 47, 4e, 38, 4b, 42, 6b, 7a, 54, 70, 31, 6e, 55, 55, 73, 73, 57, 6a, 77, 7a, 57, 34, 43, 6e], [50, 6f, 6a, 73, 6e, 63, 36, 6e, 6f, 6b, 78, 59, 49, 61, 46, 7a, 6b, 63, 71, 72, 57, 6c, 38, 4f, 6e, 6b, 6d, 65, 6b, 4d, 73, 43], [33, 4d, 7a, 68, 58, 57, 76, 52, 34, 4f, 79, 6b, 6f, 4c, 47, 7a, 6a, 59, 75, 43, 4e, 50, 64, 59, 37, 75, 58, 52, 58, 7a, 4f, 56]], [[76, 36, 50, 36, 6f, 34, 4d, 7a, 59, 6e, 56, 74, 43, 36, 65, 66, 73, 73, 76, 78, 36, 52, 31, 46, 4c, 73, 5a, 58, 41, 54, 56, 71], [48, 39, 6f, 6a, 73, 36, 34, 73, 43, 43, 41, 59, 46, 32, 32, 71, 39, 4f, 51, 76, 59, 37, 67, 58, 45, 31, 77, 77, 4b, 77, 4a, 66], [32, 76, 58, 42, 58, 75, 46, 67, 43, 56, 42, 34, 64, 37, 37, 6d, 57, 4c, 39, 72, 63, 51, 37, 7a, 6d, 38, 5a, 33, 6e, 56, 70, 64], [48, 7a, 37, 48, 4d, 6c, 33, 59, 66, 66, 4f, 47, 33, 5a, 53, 55, 37, 44, 48, 4c, 66, 58, 50, 69, 58, 32, 79, 4a, 7a, 6a, 77, 67], [66, 55, 42, 42, 78, 54, 39, 74, 64, 79, 47, 73, 46, 62, 69, 6c, 55, 6d, 37, 50, 69, 56, 67, 6b, 76, 51, 54, 6b, 32, 35, 6b, 48]], [[32, 51, 48, 32, 76, 57, 6f, 44, 61, 37, 6b, 58, 55, 32, 43, 4b, 45, 6f, 46, 58, 39, 62, 71, 78, 41, 67, 4b, 49, 48, 4e, 46, 65], [6b, 74, 43, 42, 39, 69, 49, 50, 54, 49, 61, 52, 4d, 74, 34, 64, 6d, 51, 56, 74, 4d, 4d, 46, 79, 6d, 62, 73, 4a, 54, 67, 58, 44], [38, 4d, 38, 72, 4b, 4f, 6e, 41, 55, 49, 58, 78, 39, 63, 63, 6b, 61, 78, 57, 39, 7a, 45, 6f, 52, 53, 43, 67, 73, 4c, 64, 4b, 6c], [77, 72, 38, 67, 53, 47, 35, 56, 54, 41, 6b, 4c, 49, 36, 4a, 35, 32, 4a, 61, 48, 72, 78, 4a, 56, 6b, 70, 6d, 35, 45, 59, 69, 74], [6d, 36, 69, 67, 4b, 63, 44, 5a, 4c, 45, 4b, 48, 32, 4e, 53, 50, 51, 54, 55, 64, 70, 5a, 4a, 47, 69, 36, 64, 52, 46, 75, 43, 56]], [[65, 6a, 46, 4a, 42, 63, 61, 6b, 34, 74, 36, 74, 4f, 4c, 4a, 73, 6c, 52, 6d, 58, 5a, 76, 46, 76, 39, 66, 53, 79, 4f, 32, 4e, 39], [33, 4f, 65, 4b, 39, 76, 64, 56, 4d, 69, 73, 43, 48, 6d, 73, 4a, 6b, 74, 45, 51, 4d, 52, 67, 35, 6f, 62, 7a, 69, 47, 76, 42, 50], [79, 34, 68, 6c, 34, 61, 6a, 62, 64, 69, 37, 74, 61, 79, 34, 67, 76, 46, 6a, 74, 38, 39, 75, 78, 74, 53, 64, 72, 4f, 6e, 48, 34], [73, 43, 67, 69, 4b, 59, 63, 4f, 67, 38, 50, 6a, 31, 37, 75, 47, 52, 42, 4e, 4c, 6f, 5a, 31, 71, 4e, 64, 69, 6f, 39, 76, 55, 34], [61, 46, 67, 43, 46, 59, 47, 70, 33, 77, 66, 59, 51, 78, 72, 4a, 66, 34, 35, 4d, 79, 44, 34, 56, 37, 4d, 48, 77, 5a, 41, 38, 64]], [[6d, 5a, 41, 54, 6a, 6b, 45, 6c, 65, 48, 50, 7a, 56, 34, 4f, 6f, 6a, 57, 74, 53, 4d, 67, 74, 7a, 66, 4c, 33, 68, 53, 69, 78, 46], [56, 54, 64, 63, 71, 31, 31, 4d, 77, 59, 57, 73, 32, 4d, 4b, 6e, 74, 4b, 39, 55, 6c, 45, 49, 55, 33, 31, 76, 68, 47, 41, 76, 41], [36, 67, 50, 38, 38, 6a, 4e, 35, 59, 75, 4f, 39, 43, 6f, 52, 33, 4a, 77, 64, 6e, 34, 56, 5a, 54, 42, 55, 36, 7a, 6a, 77, 63, 4f], [70, 67, 4e, 67, 70, 78, 50, 77, 77, 77, 38, 75, 31, 55, 36, 42, 50, 4f, 38, 6f, 43, 72, 7a, 57, 78, 37, 56, 34, 4e, 64, 53, 69], [4b, 33, 63, 35, 51, 55, 33, 45, 6c, 59, 73, 42, 75, 6f, 67, 4d, 58, 77, 4b, 6f, 58, 6d, 52, 44, 4d, 38, 45, 39, 79, 73, 50, 75]]],
	"strc_0": 3,
	"strc_1": 3,
	"strc": [["TXhMcmdSNjhl", "ZmVJanE=", "bEt0ZlZCUGU0"], ["WTg2ZGgzSA==", "dXlac2E0VQ==", "eWc1ZkN4dDg="], ["ODVRcDd3", "dHlpV2k2S3pvT1FTeGlOSnBzUA==", "UVN4aU5KcHNQ"]],
	"strd_2": 4,
	"strd_3": 4,
	"strd": [[[["Y0pSRVplWA==", "Zkh3UTZTRzk=", "cGpkNU41dg==", "M3N4czVvSExM"], ["UzVhT2o3Wk4=", "RUFwdTNV", "NVRRV0s=", "WmFDQlFT"], ["enJtYnZpQ1Fx", "QVNXM05FT3g=", "czR1cVQ=", "emI1MnBMeHpsTQ=="], ["T1hiSFNvbmRhYw==", "TUJScDFLaEVOTA==", "M0xsQ2Y=", "ZHNKMnJnR1Y="]], [["c29DSHlM", "SHdQVFFmRWp2WQ==", "Vm5SR0s=", "VEo4MUUyVFZpYg=="], ["bGhjcG5yWDdu", "djN3RkJPZ1NiYQ==", "Z2dnTWoxWlViUg==", "WDdobGFhbkg="], ["NkxOSkY=", "eW5lY0M=", "Wm9jb3VoTg==", "MTZZOGw4Z1NU"], ["bkk2dmJMZVBnZg==", "cFo2YmdnRlNh", "QWd3S0ppdG1Yag==", "V3hUN3NGSFA="]], [["Mk0xN3Zn", "YTlESEx3", "SU5lWHY2YVc=", "RnRBODFiRw=="], ["bkZ3WXNiOVdU", "Z3gyc3cx", "M3hXZDZ0", "YVZ5YXoxaw=="], ["R1FZOThTSVBU", "clRqZlRDZzd4", "ZVVHeEU=", "RzQydTRGSE9a"], ["bFFFNVRH", "M3dzVmJqanVF", "MjVVM0w=", "MjdGRFo="]], [["WURYdWhOTA==", "WVhmTUpL", "dTdOYTYzMQ==", "Q081TXpKTEJjUg=="], ["UDNHV3R6", "YmxzZ0dibEQ=", "dkhHV08=", "VUlOdmJDMXdT"], ["d21wZjNQS2wyaQ==", "blUyaHJKZUQ=", "VWx0VFZTYg==", "WnBXM0hLZg=="], ["V3RwRWtiZTlubg==", "aEk1Q2d4cU1o", "YmFQRkM=", "UkE2eGRhQVZBbw=="]], [["SkpScXRzZTk=", "VW9ZNHE=", "ZloxdUVXTg==", "NmFNR3Q="], ["NnBuWkNZN3k=", "dUxseGJjRU9K", "VTY2bzJTc2Q=", "OW5sckgxNg=="], ["UnJWa2hHWA==", "c2hjM3VOVWEzQg==", "RnVSbmd3Tm5N", "UkltRkVOcmdM"], ["T2ltT3puZ0FR", "NGRtVEtDR0h6Uw==", "NWtwTDJ1", "aDg5OWQ="]], [["R0Z5dGJEeG42", "dEJWTUFnUHhsdw==", "c2UyZm44eg==", "amVjdGdVUA=="], ["d29ycnhxN3hYeA==", "Z1hkOXJ4OW4zdA==", "SVJ3d0tjR1FFTg==", "SDlzTnVESkk="], ["cldwZEZBa2FEVA==", "a29rVzdC", "VGJmeGZsR2E=", "bjhmY3NCU1JPYw=="], ["MXVVb1lDVQ==", "M1dFVXFWOQ==", "Z1hENWxM", "QnJmT0YzZQ=="]]], [[["MWhibzVsVmlsYg==", "OFVHdTk=", "d0x1RUFZblZNeQ==", "MWduMVM0"], ["RnhyNFhQVg==", "Z0F1eENnZnc=", "OEd6MlNPUFM1dQ==", "SG8zRVNyWQ=="], ["WldSb3NMU3V0Nw==", "d3R3RXJDc0NJ", "cXp0anpIcVJs", "djVoRGZ1Y21q"], ["Qm1EOGVNNHo=", "T0sycTNrRUhu", "b2RQYU96WVY=", "dXNuclpk"]], [["NXBhYncyZnJ3", "V0Fld0J6eg==", "QXE5ajQ=", "WWdSSG9WNnN5Zw=="], ["aGh3bW12OW8=", "aXlxUFpaS01v", "NVhwSU8=", "VEZKSndZdQ=="], ["SEQ4c0Nm", "ZVdxWmw=", "QWtwRWN3WndM", "RFR1UkdMSmQ="], ["UmoxdkYxWQ==", "cW5HOGl0aA==", "T25BSmpxUjU=", "eUp5M3JYWVFM"]], [["Z0xIUE1kYzhFTw==", "emczdHV6c0pj", "M2ZYNXY=", "TzdJS2xR"], ["cWIxWVRRZHE0", "cXlCUW4=", "N3lGajlLVkNiMQ==", "Z2xlMkVV"], ["dWRtUWxRc1dEdQ==", "cDFpeEY=", "UlJRdjlRcWM0", "Y1JNeEw="], ["M2xPUVM=", "ZE56Uk1J", "QWdQZEN1eA==", "Z01iUmx3UUMz"]], [["QmxuY2VKSg==", "YWxxMm5LZg==", "dHB4SUdLVGF6OA==", "NDF6WEJabGo="], ["aXV0UVlzbXQ=", "Q2xmZVY0", "RFVpdVNQaVM=", "OVU1bTU4SGFz"], ["TlRWZUZMV3cybg==", "TXNLdWJRQlNkOA==", "TXF6NWk=", "Z1FVc3JFeg=="], ["bDY5eFI=", "ekNxVWpQUmU=", "UzYzWHY3ZUZsUA==", "RFg0dUx4cE4="]], [["WnVoRGc0cjdJ", "cWxrcXNWeQ==", "UFVlcmo2dFI=", "SVZaUkg5MUVjNQ=="], ["V1M5T2VuSA==", "eDRCdEk5Zzg=", "blM3aUlN", "eDZMN1FYWnFSMg=="], ["R21ZbzJVeXk=", "Zm1jYjl5UmdD", "dGpVNnhpQmdn", "Z3RmWEpUVmJK"], ["Q3RPZ09KUmZy", "VmhYRXpoSw==", "QXRNNmdkMXVC", "REc1WU1BNElR"]], [["MkFlTjk2bld4", "TXRuTnBCcHBydQ==", "VjRvVzMyRU9R", "UHNsWWpi"], ["MjFiTXQ=", "Q2M0dEc=", "ek5xeHVB", "dWZ0RldW"], ["NFF2bURjbWF4RA==", "Z3VqVzJSMzFEYw==", "eDFsSHR0", "OGFsWUgyaw=="], ["UVBGczllYg==", "QW13U2JDaUE=", "aWVya2dXdlk0cg==", "NVdGRXM="]]], [[["WGtQa056Tjdy", "MmxyaFVnVzZQcg==", "aHVEWm9kVA==", "VXJTNkNlMmc="], ["OG1XcTNGblU5cQ==", "S3NmeW03Nw==", "a0FPNkJsOUw=", "cXRPb0ZvakY="], ["Vnp3NnQ=", "Z2JpQlJzRA==", "Nmw5M0x1THpnNQ==", "WUt6NEV2TTRV"], ["b1VqR0Nn", "dTh6c24=", "c2pHZVh0dTc=", "NWJYVDRaSQ=="]], [["VlZnZ1BhT3Ft", "RUtmcXI=", "VmRVcW4=", "QkVwS2k="], ["UEMyWUxqMVc=", "UEFpY3M5", "a3BSZ1JweGUxbA==", "aWFNbjFY"], ["VURNVGdJZDY=", "Smc0SUhhYXI=", "bUk2bXFHR2pG", "a1VDNmxaUEdu"], ["S3padWJXNUpMaQ==", "a0NHTjNXRHpmNw==", "MzFCelo=", "dWtJN1htYWg5"]], [["eTFRQmhj", "Z25mOU1JcktQcg==", "cjZnaHg=", "dmdSRkQ="], ["cTFTUEJ3eUk=", "QTJXUE9Hbmo=", "c1E1UDFuRnha", "b1VxalRYcQ=="], ["M2Z1Yjd5cQ==", "Q0NnZENJQw==", "Z0N4cWhn", "WTJVNlVRdHk="], ["bWs4Ull5aw==", "cUpaNGNIMQ==", "T3gxN0piU0t0Rw==", "UzJQZG45"]], [["ckRSV2ZEa2lG", "NERTU3lTSw==", "cFFWemhreWdx", "Q29OODJX"], ["Z2Q5RTgxWQ==", "RGc2Yml3R0c3bw==", "Y3hFVE1iWEM=", "Q3Zwb0pnSw=="], ["aHZEcVpL", "ODJ4QzZEcW15", "ZXR5NnFHTVI=", "eWt6N2ZKUTlN"], ["TlJuQjl4NEw=", "RTVzRm9uS2dzRw==", "ZzFrSDVHWQ==", "WEU1SnlS"]], [["ZjhIck9oeTF3", "djJMSkZYeURkNQ==", "OEl6MXB2Sg==", "cUVKeWszVkpp"], ["MlBqMVdpRA==", "eG5GdmZY", "Skx4Zkk=", "emFKSVNKV201"], ["UUZDbWdl", "SlJaUnd0dmY=", "ZkdkNEdHZ0U=", "N2w3WXZX"], ["b3hGVFk5emFN", "a3JRU3lCbQ==", "MWdmZE1Ia2hWOA==", "Y2RyMTlIUnlwVg=="]], [["ZmRnQjdt", "WXFMMXo=", "QnBSZnJPdQ==", "MmpVcXVvZA=="], ["cm5LYlhERXpUdQ==", "Y2k0SWVmcHZu", "UHkzcUx3ZndjSw==", "M0laVno="], ["aDdQMVdCNHA=", "aFFFVm0=", "d0V6NEFKdHVZ", "b2ZndEdMV1hXVw=="], ["bkVTVDFhdVY=", "bTV6Mzh0", "cGx2SE8=", "eVpVNXhuWQ=="]]], [[["NGVUREZUNzFuTQ==", "RWpFT1JsTjQ=", "RFBLTlJjMw==", "NUlxNkpG"], ["V2tORUJDZWJk", "dFZpckJ5Tkk0WA==", "YlZoV1duVGth", "M094VFlnR2VV"], ["Z0VIUVEz", "dTRqbVFzVg==", "Q3pHc0RzZ2NGTQ==", "d1NhS2Q="], ["a3dpTXc=", "eXlxU0d4T05nZQ==", "T0M1NGdLMWIx", "R0g4eGl1Uw=="]], [["anhsRVJ5ZzZY", "ejQ3ZU4=", "cmcxckwx", "VEg0cTU="], ["THBJZkFvQlZZNA==", "MXZaNVlKdA==", "ZXkyMnJOWTE=", "RDVwVHNC"], ["NXlYMkw=", "SExrSVg1", "OVpPc1hJdkw=", "eFhxdndTSjdP"], ["c0VYd2JJMU5nQw==", "WjRabWdGaUtV", "c25BSlV6SURxRQ==", "U3h1aWVp"]], [["bmVya3I=", "MmJadWZi", "VTZRYlMzeQ==", "ZUdXQmlKZWg1"], ["QnRRZ2hVZg==", "bVdvN2w=", "cTFsTDNUZ3lqTQ==", "VUdzN0xPMjdhZw=="], ["TUFndnNSUURuSQ==", "TW1IUlYyNQ==", "d09JbEdRZUpUbA==", "NmtDekM="], ["NWNNV3JTUVBuZQ==", "bXRtSVZ5OU9EYQ==", "alBQdjlUQg==", "SzF2SldPV2VoOQ=="]], [["NFluUWR4R3py", "QVBNemx6VzVrRQ==", "azlTMUdz", "dGxjeTk0R2tiVw=="], ["T3JFa3E2S1JU", "M2lKa2dXa3JDUQ==", "ZjZFbDhqWkU=", "RnNlZ1BhbFE="], ["NWNWc2RkVVhB", "SnN1d2dLRQ==", "aWM2dWloaw==", "cU80UEU4dG5rdg=="], ["OGtXQnVa", "aGkxMlBpeER6", "ZUxkcFE=", "M3JjdE8="]], [["UG1Nd3dYZw==", "NUFpM1NC", "dFBBQlhFcHR0", "dGc4ZzdNOFlO"], ["R0pSSFo=", "NEM4MXJkUA==", "aUV2YkZQZTE2", "Z2Vwekd1UEU2ZA=="], ["Vkl6TEc=", "NThlTmc=", "eENRcjVRb2dWbA==", "amlaOEtWbHVa"], ["T1BWd0Y0", "U2hxdHBBaGdw", "T3Q3ZldkdA==", "cjlxa00="]], [["OE9ycHo=", "VHJXRmhMY0h1", "ekNNUXBRQ3pp", "V2d4UVRX"], ["R1pQMWNDRQ==", "YXhEOUlu", "UWNxSjYz", "czhaSVc="], ["YWVPOTU=", "N25kT0hUd21B", "N3NqV3pp", "dm5NV2xUZVhOZg=="], ["NWczd1ZmSw==", "MU1hU0hoNHQxdg==", "WTExRVFq", "U3N0OFh1Y0M="]]], [[["bG9pZXV5eE40Sw==", "eUx2WWN4", "NzU0ZEhkdlY=", "U2pxd0o="], ["aE1SUmxRVA==", "V0plNnpZUTg=", "VDk3bGxRZlVkRA==", "elFlSlFHazM="], ["NGROWmMyZw==", "V2xaeW4=", "VTFiMVVKU3phZA==", "d1prV0NGWXVQ"], ["T1NLR3M=", "SXZKRXdK", "ZWNCVlZpb1dncQ==", "TjNTV296OEJy"]], [["U3Z5ajI1MWVaOA==", "ZjVwcGE=", "S1lJS1I=", "V3JNNXBY"], ["dVRPejM=", "djRDZzlvUGU=", "Mmw3Wjg=", "T1Bsb0NoYXRzYg=="], ["VmlYTk1qTQ==", "Rjl3eGFPYw==", "RGZKYjRtQnN6Zw==", "VVlxOFdoMg=="], ["Z2hib3dSa1Q=", "ODhSWng=", "Z2NNZkZsSWg=", "c210Q1Y="]], [["amFtQ21Qbk5n", "N2M0QkJ6Zg==", "bFV0WGRSMVl3", "bjdmVmo="], ["TEJSZ0M=", "SE14SkJoYW8=", "UEM1UmlZ", "WkhHa1Y="], ["ZHM1dHU=", "UXdJaHdxdA==", "bmNmZ3lvaEo=", "NmxqTHlIRHN3NQ=="], ["ZmE0VnhBYUVLeA==", "aE00QXJzcTE=", "cmx1NlQzSE4=", "WGR4dGY="]], [["WTdJb0NyTg==", "cTIzZGR3ZA==", "c1NnZ2c=", "dHN2OFIxcDE="], ["TjU3dTFweXBsdA==", "U216NklGRzQ=", "cmpndlZ6OEJTOA==", "UHJqQnJQZWxx"], ["U1haeUJXMQ==", "VGVOM2JsTTFt", "U1l5eks=", "ajJkbWt4Qw=="], ["Z0hoc2dn", "M3YxNTRqMjJO", "RlI4eWxE", "azZlTFE="]], [["NENaa3RvRA==", "b2Fpc2ZJZGdZ", "cXBzZE81", "cXc5TU9y"], ["UjdsR2R5NVdjZA==", "TDF5eVJ6Z1pEVQ==", "SlJBMVNJ", "Q09hMjk3ZGd3"], ["THpIT2s0VjVj", "Qm9CbjhuaTk=", "Tkd1VDd5RnI=", "OXNrTkRpSXRzVw=="], ["Rkt1NUREZWQx", "RU41SFd3M2c=", "bXZUTXg=", "dXFFYlNYc1E4"]], [["Zkt2WUxGcEdI", "aEI4U29Z", "WFREcEtaWGc=", "RElyTDU="], ["UFFybWR4ZnE=", "UDdZY2ZwRHlY", "dkRqa3EzZUd1", "SkRTZ05wT2s="], ["S01nQ0VadQ==", "UnpIdzFt", "aFVRUXpIRWFt", "T25ZZ01wdE4="], ["OVFiZnp3SG9z", "SkxyYmtT", "eWdvR08=", "ZmRkYVJudW8="]]], [[["RkQyb0JKbnVUZg==", "R0tibUhTWA==", "bVE1Wlhnd2M=", "Z0ZtZWJRag=="], ["aFZBNHBKSA==", "ZGdNN3U=", "VEpxY0E=", "VXVrMjEy"], ["bm1FMU4=", "T01IbkhCSw==", "Vk5oTVF1OQ==", "QldQZTNTZTI="], ["SW12T2IzamJLQg==", "R0d4UEFaT3M4", "ZzVnNnVoSg==", "aEQ1TnBB"]], [["cGVOdzdwVkw=", "UldUYUNTNm9G", "ZzRKdGp0Qg==", "cXR1RXZnVw=="], ["bEtRc0VyQw==", "Y0hNbTc=", "MnpGSFllM1FV", "R1pHcG9n"], ["SXJ4Mkc=", "QzN3TzJQRw==", "T2liblo=", "UXpnQXVpdmI="], ["WnpyNk5l", "RTdYREdYeg==", "VHJIcU9PTHA=", "dTFoenZWTmdnOQ=="]], [["c3NhVmdl", "ZTR3RElz", "SzNvSWFqQ29IZw==", "QWRlOXpFbA=="], ["Wmd3NjRkOXk2Rw==", "VFJiQ3NHYQ==", "NnFRS1pD", "MmZSazliSGk="], ["WldPNlV2bQ==", "cTV0bEw=", "WVZSdUZ4OUp6", "eFhtTU9IV21qYQ=="], ["NUdlZ0NpbWc3", "MjNJaUdlZ1Q=", "SjdtaDZveVQ=", "RVZqVUE="]], [["M1lKVzI=", "VDNCZGk=", "Yldnd2tsSUdjQg==", "d1NFNXI="], ["R0dwa1RLag==", "dmxjSEl5ZnBF", "TzVyeG0=", "Y0lYOFM3Zm1MVA=="], ["eHhoNDFKdkZjUw==", "U2dFa2hHVg==", "QmtVSnY=", "VkxCRmNWb00="], ["cEI4SEFRbkpmQw==", "RnBvSXl0", "WDRScEJjdUFO", "M0Nsc0puOFc5WQ=="]], [["eG5MaUp3", "NmQ1QmdJ", "ZHd4N3FSNzU=", "akNUbnhEdFp1"], ["QXpRWGdZdA==", "UldxSlhwZDFr", "N3ozY2Y=", "NEdoeVVUTg=="], ["Nm1zenk=", "Vkg3NFUxZE0=", "QUI0ck5u", "RW1kMkcyUkFr"], ["YVBydnk=", "YXNxTXB6Vm90", "YWdKS1hsaA==", "bGVpNENJRHQ="]], [["VlBFMzFYZQ==", "ckVYbEc=", "U2VFUTY0Qg==", "ejludjV0cHVX"], ["VnR5VjhnWHAx", "T0Rta05yMjJ0Qg==", "VTZMdzg3aw==", "SVJwWkx0Tnk4"], ["clhWTXhnQw==", "Z1ZLc3ljaDhZ", "ZTdLSkE5UFE=", "VURsWE5kS0M="], ["eUp6bVNzWk1Gbw==", "bER1bVc1b1BT", "M2tXemZtR3RjVw==", "YTVNNWZK"]]]],
	"stre_0": 2,
	"stre_1": 2,
	"stre_2": 2,
	"stre_3": 2,
	"stre": [[[["cTY1V0s=", "OWtmZzk4cmVt"], ["RUNnajdKMmM4NA==", "cmhhcnZnaQ=="]], [["eW5yUlhtUzFEWA==", "bXZsWFh2QVoyTA=="], ["bDNhUHJGOA==", "WmFNNlg="]]], [[["VFVLam5qTjRKTA==", "ZldIZmtT"], ["azRiUkpFNElY", "REdYaGxTRg=="]], [["d1MzTlRCZHVEWQ==", "dno2Yk5PZ1FQ"], ["eERIb1RyUGg=", "T2JTT3Y="]]]]
}
```

### Json Decode
```bash
JSON_DECODE:
Strings@55cf7c3830a0
stra_0: '5';
stra_1: '5';
stra: 
'Q48aFE', 'oKNtL', 'MQNN5E', 'vtBl33aPMI', 'QOkKc'
'2DZMBSnCs', 'Kg83Zs1', 's1T2Mdgm', 'FgbHhpI', 'ulC9A'
'18x31G1a', '1Bw1ivbppV', '8a5GU', 'umjBVj3kj1', 'kaskyz'
'cMBSuKbd', 'W8DZsdopi', 'pI6aXvEu', 'KUasRy4Z6', 'yrwdN4TspV'
'Byu4c8m9s', 'B1FuT2pb6Z', 'o33u6Ubg', '6dFpfpjXg', 'gaP9n';
strb: 
'39', '59', '4a', '59', '54', '37', '64', '57', '4b', '51', '44', '55', '75', '6e', '33', '75', '50', '4a', '45', '39', '78', '37', '72', '62', '56', '6f', '6c', '49', '70', '36', '41', '52'
'76', '53', '54', '53', '35', '6e', '4e', '36', '58', '4c', '5a', '46', '46', '68', '6c', '6b', '35', '63', '72', '6a', '43', '54', '4a', '61', '4e', '4a', '74', '50', '66', '77', '68', '62'
'76', '70', '36', '6e', '56', '6a', '50', '6f', '66', '47', '4e', '38', '4b', '42', '6b', '7a', '54', '70', '31', '6e', '55', '55', '73', '73', '57', '6a', '77', '7a', '57', '34', '43', '6e'
'50', '6f', '6a', '73', '6e', '63', '36', '6e', '6f', '6b', '78', '59', '49', '61', '46', '7a', '6b', '63', '71', '72', '57', '6c', '38', '4f', '6e', '6b', '6d', '65', '6b', '4d', '73', '43'
'33', '4d', '7a', '68', '58', '57', '76', '52', '34', '4f', '79', '6b', '6f', '4c', '47', '7a', '6a', '59', '75', '43', '4e', '50', '64', '59', '37', '75', '58', '52', '58', '7a', '4f', '56'

'76', '36', '50', '36', '6f', '34', '4d', '7a', '59', '6e', '56', '74', '43', '36', '65', '66', '73', '73', '76', '78', '36', '52', '31', '46', '4c', '73', '5a', '58', '41', '54', '56', '71'
'48', '39', '6f', '6a', '73', '36', '34', '73', '43', '43', '41', '59', '46', '32', '32', '71', '39', '4f', '51', '76', '59', '37', '67', '58', '45', '31', '77', '77', '4b', '77', '4a', '66'
'32', '76', '58', '42', '58', '75', '46', '67', '43', '56', '42', '34', '64', '37', '37', '6d', '57', '4c', '39', '72', '63', '51', '37', '7a', '6d', '38', '5a', '33', '6e', '56', '70', '64'
'48', '7a', '37', '48', '4d', '6c', '33', '59', '66', '66', '4f', '47', '33', '5a', '53', '55', '37', '44', '48', '4c', '66', '58', '50', '69', '58', '32', '79', '4a', '7a', '6a', '77', '67'
'66', '55', '42', '42', '78', '54', '39', '74', '64', '79', '47', '73', '46', '62', '69', '6c', '55', '6d', '37', '50', '69', '56', '67', '6b', '76', '51', '54', '6b', '32', '35', '6b', '48'

'32', '51', '48', '32', '76', '57', '6f', '44', '61', '37', '6b', '58', '55', '32', '43', '4b', '45', '6f', '46', '58', '39', '62', '71', '78', '41', '67', '4b', '49', '48', '4e', '46', '65'
'6b', '74', '43', '42', '39', '69', '49', '50', '54', '49', '61', '52', '4d', '74', '34', '64', '6d', '51', '56', '74', '4d', '4d', '46', '79', '6d', '62', '73', '4a', '54', '67', '58', '44'
'38', '4d', '38', '72', '4b', '4f', '6e', '41', '55', '49', '58', '78', '39', '63', '63', '6b', '61', '78', '57', '39', '7a', '45', '6f', '52', '53', '43', '67', '73', '4c', '64', '4b', '6c'
'77', '72', '38', '67', '53', '47', '35', '56', '54', '41', '6b', '4c', '49', '36', '4a', '35', '32', '4a', '61', '48', '72', '78', '4a', '56', '6b', '70', '6d', '35', '45', '59', '69', '74'
'6d', '36', '69', '67', '4b', '63', '44', '5a', '4c', '45', '4b', '48', '32', '4e', '53', '50', '51', '54', '55', '64', '70', '5a', '4a', '47', '69', '36', '64', '52', '46', '75', '43', '56'

'65', '6a', '46', '4a', '42', '63', '61', '6b', '34', '74', '36', '74', '4f', '4c', '4a', '73', '6c', '52', '6d', '58', '5a', '76', '46', '76', '39', '66', '53', '79', '4f', '32', '4e', '39'
'33', '4f', '65', '4b', '39', '76', '64', '56', '4d', '69', '73', '43', '48', '6d', '73', '4a', '6b', '74', '45', '51', '4d', '52', '67', '35', '6f', '62', '7a', '69', '47', '76', '42', '50'
'79', '34', '68', '6c', '34', '61', '6a', '62', '64', '69', '37', '74', '61', '79', '34', '67', '76', '46', '6a', '74', '38', '39', '75', '78', '74', '53', '64', '72', '4f', '6e', '48', '34'
'73', '43', '67', '69', '4b', '59', '63', '4f', '67', '38', '50', '6a', '31', '37', '75', '47', '52', '42', '4e', '4c', '6f', '5a', '31', '71', '4e', '64', '69', '6f', '39', '76', '55', '34'
'61', '46', '67', '43', '46', '59', '47', '70', '33', '77', '66', '59', '51', '78', '72', '4a', '66', '34', '35', '4d', '79', '44', '34', '56', '37', '4d', '48', '77', '5a', '41', '38', '64'

'6d', '5a', '41', '54', '6a', '6b', '45', '6c', '65', '48', '50', '7a', '56', '34', '4f', '6f', '6a', '57', '74', '53', '4d', '67', '74', '7a', '66', '4c', '33', '68', '53', '69', '78', '46'
'56', '54', '64', '63', '71', '31', '31', '4d', '77', '59', '57', '73', '32', '4d', '4b', '6e', '74', '4b', '39', '55', '6c', '45', '49', '55', '33', '31', '76', '68', '47', '41', '76', '41'
'36', '67', '50', '38', '38', '6a', '4e', '35', '59', '75', '4f', '39', '43', '6f', '52', '33', '4a', '77', '64', '6e', '34', '56', '5a', '54', '42', '55', '36', '7a', '6a', '77', '63', '4f'
'70', '67', '4e', '67', '70', '78', '50', '77', '77', '77', '38', '75', '31', '55', '36', '42', '50', '4f', '38', '6f', '43', '72', '7a', '57', '78', '37', '56', '34', '4e', '64', '53', '69'
'4b', '33', '63', '35', '51', '55', '33', '45', '6c', '59', '73', '42', '75', '6f', '67', '4d', '58', '77', '4b', '6f', '58', '6d', '52', '44', '4d', '38', '45', '39', '79', '73', '50', '75';
strc_0: '3';
strc_1: '3';
strc: 
'MxLrgR68e', 'feIjq', 'lKtfVBPe4'
'Y86dh3H', 'uyZsa4U', 'yg5fCxt8'
'85Qp7w', 'tyiWi6KzoOQSxiNJpsP', 'QSxiNJpsP';
strd_2: '4';
strd_3: '4';
strd: 
'cJREZeX', 'fHwQ6SG9', 'pjd5N5v', '3sxs5oHLL'
'S5aOj7ZN', 'EApu3U', '5TQWK', 'ZaCBQS'
'zrmbviCQq', 'ASW3NEOx', 's4uqT', 'zb52pLxzlM'
'OXbHSondac', 'MBRp1KhENL', '3LlCf', 'dsJ2rgGV'

'soCHyL', 'HwPTQfEjvY', 'VnRGK', 'TJ81E2TVib'
'lhcpnrX7n', 'v3wFBOgSba', 'gggMj1ZUbR', 'X7hlaanH'
'6LNJF', 'ynecC', 'ZocouhN', '16Y8l8gST'
'nI6vbLePgf', 'pZ6bggFSa', 'AgwKJitmXj', 'WxT7sFHP'

'2M17vg', 'a9DHLw', 'INeXv6aW', 'FtA81bG'
'nFwYsb9WT', 'gx2sw1', '3xWd6t', 'aVyaz1k'
'GQY98SIPT', 'rTjfTCg7x', 'eUGxE', 'G42u4FHOZ'
'lQE5TG', '3wsVbjjuE', '25U3L', '27FDZ'

'YDXuhNL', 'YXfMJK', 'u7Na631', 'CO5MzJLBcR'
'P3GWtz', 'blsgGblD', 'vHGWO', 'UINvbC1wS'
'wmpf3PKl2i', 'nU2hrJeD', 'UltTVSb', 'ZpW3HKf'
'WtpEkbe9nn', 'hI5CgxqMh', 'baPFC', 'RA6xdaAVAo'

'JJRqtse9', 'UoY4q', 'fZ1uEWN', '6aMGt'
'6pnZCY7y', 'uLlxbcEOJ', 'U66o2Ssd', '9nlrH16'
'RrVkhGX', 'shc3uNUa3B', 'FuRngwNnM', 'RImFENrgL'
'OimOzngAQ', '4dmTKCGHzS', '5kpL2u', 'h899d'

'GFytbDxn6', 'tBVMAgPxlw', 'se2fn8z', 'jectgUP'
'worrxq7xXx', 'gXd9rx9n3t', 'IRwwKcGQEN', 'H9sNuDJI'
'rWpdFAkaDT', 'kokW7B', 'TbfxflGa', 'n8fcsBSROc'
'1uUoYCU', '3WEUqV9', 'gXD5lL', 'BrfOF3e'


'1hbo5lVilb', '8UGu9', 'wLuEAYnVMy', '1gn1S4'
'Fxr4XPV', 'gAuxCgfw', '8Gz2SOPS5u', 'Ho3ESrY'
'ZWRosLSut7', 'wtwErCsCI', 'qztjzHqRl', 'v5hDfucmj'
'BmD8eM4z', 'OK2q3kEHn', 'odPaOzYV', 'usnrZd'

'5pabw2frw', 'WAewBzz', 'Aq9j4', 'YgRHoV6syg'
'hhwmmv9o', 'iyqPZZKMo', '5XpIO', 'TFJJwYu'
'HD8sCf', 'eWqZl', 'AkpEcwZwL', 'DTuRGLJd'
'Rj1vF1Y', 'qnG8ith', 'OnAJjqR5', 'yJy3rXYQL'

'gLHPMdc8EO', 'zg3tuzsJc', '3fX5v', 'O7IKlQ'
'qb1YTQdq4', 'qyBQn', '7yFj9KVCb1', 'gle2EU'
'udmQlQsWDu', 'p1ixF', 'RRQv9Qqc4', 'cRMxL'
'3lOQS', 'dNzRMI', 'AgPdCux', 'gMbRlwQC3'

'BlnceJJ', 'alq2nKf', 'tpxIGKTaz8', '41zXBZlj'
'iutQYsmt', 'ClfeV4', 'DUiuSPiS', '9U5m58Has'
'NTVeFLWw2n', 'MsKubQBSd8', 'Mqz5i', 'gQUsrEz'
'l69xR', 'zCqUjPRe', 'S63Xv7eFlP', 'DX4uLxpN'

'ZuhDg4r7I', 'qlkqsVy', 'PUerj6tR', 'IVZRH91Ec5'
'WS9OenH', 'x4BtI9g8', 'nS7iIM', 'x6L7QXZqR2'
'GmYo2Uyy', 'fmcb9yRgC', 'tjU6xiBgg', 'gtfXJTVbJ'
'CtOgOJRfr', 'VhXEzhK', 'AtM6gd1uB', 'DG5YMA4IQ'

'2AeN96nWx', 'MtnNpBppru', 'V4oW32EOQ', 'PslYjb'
'21bMt', 'Cc4tG', 'zNqxuA', 'uftFWV'
'4QvmDcmaxD', 'gujW2R31Dc', 'x1lHtt', '8alYH2k'
'QPFs9eb', 'AmwSbCiA', 'ierkgWvY4r', '5WFEs'


'XkPkNzN7r', '2lrhUgW6Pr', 'huDZodT', 'UrS6Ce2g'
'8mWq3FnU9q', 'Ksfym77', 'kAO6Bl9L', 'qtOoFojF'
'Vzw6t', 'gbiBRsD', '6l93LuLzg5', 'YKz4EvM4U'
'oUjGCg', 'u8zsn', 'sjGeXtu7', '5bXT4ZI'

'VVggPaOqm', 'EKfqr', 'VdUqn', 'BEpKi'
'PC2YLj1W', 'PAics9', 'kpRgRpxe1l', 'iaMn1X'
'UDMTgId6', 'Jg4IHaar', 'mI6mqGGjF', 'kUC6lZPGn'
'KzZubW5JLi', 'kCGN3WDzf7', '31BzZ', 'ukI7Xmah9'

'y1QBhc', 'gnf9MIrKPr', 'r6ghx', 'vgRFD'
'q1SPBwyI', 'A2WPOGnj', 'sQ5P1nFxZ', 'oUqjTXq'
'3fub7yq', 'CCgdCIC', 'gCxqhg', 'Y2U6UQty'
'mk8RYyk', 'qJZ4cH1', 'Ox17JbSKtG', 'S2Pdn9'

'rDRWfDkiF', '4DSSySK', 'pQVzhkygq', 'CoN82W'
'gd9E81Y', 'Dg6biwGG7o', 'cxETMbXC', 'CvpoJgK'
'hvDqZK', '82xC6Dqmy', 'ety6qGMR', 'ykz7fJQ9M'
'NRnB9x4L', 'E5sFonKgsG', 'g1kH5GY', 'XE5JyR'

'f8HrOhy1w', 'v2LJFXyDd5', '8Iz1pvJ', 'qEJyk3VJi'
'2Pj1WiD', 'xnFvfX', 'JLxfI', 'zaJISJWm5'
'QFCmge', 'JRZRwtvf', 'fGd4GGgE', '7l7YvW'
'oxFTY9zaM', 'krQSyBm', '1gfdMHkhV8', 'cdr19HRypV'

'fdgB7m', 'YqL1z', 'BpRfrOu', '2jUquod'
'rnKbXDEzTu', 'ci4Iefpvn', 'Py3qLwfwcK', '3IZVz'
'h7P1WB4p', 'hQEVm', 'wEz4AJtuY', 'ofgtGLWXWW'
'nEST1auV', 'm5z38t', 'plvHO', 'yZU5xnY'


'4eTDFT71nM', 'EjEORlN4', 'DPKNRc3', '5Iq6JF'
'WkNEBCebd', 'tVirByNI4X', 'bVhWWnTka', '3OxTYgGeU'
'gEHQQ3', 'u4jmQsV', 'CzGsDsgcFM', 'wSaKd'
'kwiMw', 'yyqSGxONge', 'OC54gK1b1', 'GH8xiuS'

'jxlERyg6X', 'z47eN', 'rg1rL1', 'TH4q5'
'LpIfAoBVY4', '1vZ5YJt', 'ey22rNY1', 'D5pTsB'
'5yX2L', 'HLkIX5', '9ZOsXIvL', 'xXqvwSJ7O'
'sEXwbI1NgC', 'Z4ZmgFiKU', 'snAJUzIDqE', 'Sxuiei'

'nerkr', '2bZufb', 'U6QbS3y', 'eGWBiJeh5'
'BtQghUf', 'mWo7l', 'q1lL3TgyjM', 'UGs7LO27ag'
'MAgvsRQDnI', 'MmHRV25', 'wOIlGQeJTl', '6kCzC'
'5cMWrSQPne', 'mtmIVy9ODa', 'jPPv9TB', 'K1vJWOWeh9'

'4YnQdxGzr', 'APMzlzW5kE', 'k9S1Gs', 'tlcy94GkbW'
'OrEkq6KRT', '3iJkgWkrCQ', 'f6El8jZE', 'FsegPalQ'
'5cVsddUXA', 'JsuwgKE', 'ic6uihk', 'qO4PE8tnkv'
'8kWBuZ', 'hi12PixDz', 'eLdpQ', '3rctO'

'PmMwwXg', '5Ai3SB', 'tPABXEptt', 'tg8g7M8YN'
'GJRHZ', '4C81rdP', 'iEvbFPe16', 'gepzGuPE6d'
'VIzLG', '58eNg', 'xCQr5QogVl', 'jiZ8KVluZ'
'OPVwF4', 'ShqtpAhgp', 'Ot7fWdt', 'r9qkM'

'8Orpz', 'TrWFhLcHu', 'zCMQpQCzi', 'WgxQTW'
'GZP1cCE', 'axD9In', 'QcqJ63', 's8ZIW'
'aeO95', '7ndOHTwmA', '7sjWzi', 'vnMWlTeXNf'
'5g3wVfK', '1MaSHh4t1v', 'Y11EQj', 'Sst8XucC'


'loieuyxN4K', 'yLvYcx', '754dHdvV', 'SjqwJ'
'hMRRlQT', 'WJe6zYQ8', 'T97llQfUdD', 'zQeJQGk3'
'4dNZc2g', 'WlZyn', 'U1b1UJSzad', 'wZkWCFYuP'
'OSKGs', 'IvJEwJ', 'ecBVVioWgq', 'N3SWoz8Br'

'Svyj251eZ8', 'f5ppa', 'KYIKR', 'WrM5pX'
'uTOz3', 'v4Cg9oPe', '2l7Z8', 'OPloChatsb'
'ViXNMjM', 'F9wxaOc', 'DfJb4mBszg', 'UYq8Wh2'
'ghbowRkT', '88RZx', 'gcMfFlIh', 'smtCV'

'jamCmPnNg', '7c4BBzf', 'lUtXdR1Yw', 'n7fVj'
'LBRgC', 'HMxJBhao', 'PC5RiY', 'ZHGkV'
'ds5tu', 'QwIhwqt', 'ncfgyohJ', '6ljLyHDsw5'
'fa4VxAaEKx', 'hM4Arsq1', 'rlu6T3HN', 'Xdxtf'

'Y7IoCrN', 'q23ddwd', 'sSggg', 'tsv8R1p1'
'N57u1pyplt', 'Smz6IFG4', 'rjgvVz8BS8', 'PrjBrPelq'
'SXZyBW1', 'TeN3blM1m', 'SYyzK', 'j2dmkxC'
'gHhsgg', '3v154j22N', 'FR8ylD', 'k6eLQ'

'4CZktoD', 'oaisfIdgY', 'qpsdO5', 'qw9MOr'
'R7lGdy5Wcd', 'L1yyRzgZDU', 'JRA1SI', 'COa297dgw'
'LzHOk4V5c', 'BoBn8ni9', 'NGuT7yFr', '9skNDiItsW'
'FKu5DDed1', 'EN5HWw3g', 'mvTMx', 'uqEbSXsQ8'

'fKvYLFpGH', 'hB8SoY', 'XTDpKZXg', 'DIrL5'
'PQrmdxfq', 'P7YcfpDyX', 'vDjkq3eGu', 'JDSgNpOk'
'KMgCEZu', 'RzHw1m', 'hUQQzHEam', 'OnYgMptN'
'9QbfzwHos', 'JLrbkS', 'ygoGO', 'fddaRnuo'


'FD2oBJnuTf', 'GKbmHSX', 'mQ5ZXgwc', 'gFmebQj'
'hVA4pJH', 'dgM7u', 'TJqcA', 'Uuk212'
'nmE1N', 'OMHnHBK', 'VNhMQu9', 'BWPe3Se2'
'ImvOb3jbKB', 'GGxPAZOs8', 'g5g6uhJ', 'hD5NpA'

'peNw7pVL', 'RWTaCS6oF', 'g4JtjtB', 'qtuEvgW'
'lKQsErC', 'cHMm7', '2zFHYe3QU', 'GZGpog'
'Irx2G', 'C3wO2PG', 'OibnZ', 'QzgAuivb'
'Zzr6Ne', 'E7XDGXz', 'TrHqOOLp', 'u1hzvVNgg9'

'ssaVge', 'e4wDIs', 'K3oIajCoHg', 'Ade9zEl'
'Zgw64d9y6G', 'TRbCsGa', '6qQKZC', '2fRk9bHi'
'ZWO6Uvm', 'q5tlL', 'YVRuFx9Jz', 'xXmMOHWmja'
'5GegCimg7', '23IiGegT', 'J7mh6oyT', 'EVjUA'

'3YJW2', 'T3Bdi', 'bWgwklIGcB', 'wSE5r'
'GGpkTKj', 'vlcHIyfpE', 'O5rxm', 'cIX8S7fmLT'
'xxh41JvFcS', 'SgEkhGV', 'BkUJv', 'VLBFcVoM'
'pB8HAQnJfC', 'FpoIyt', 'X4RpBcuAN', '3ClsJn8W9Y'

'xnLiJw', '6d5BgI', 'dwx7qR75', 'jCTnxDtZu'
'AzQXgYt', 'RWqJXpd1k', '7z3cf', '4GhyUTN'
'6mszy', 'VH74U1dM', 'AB4rNn', 'Emd2G2RAk'
'aPrvy', 'asqMpzVot', 'agJKXlh', 'lei4CIDt'

'VPE31Xe', 'rEXlG', 'SeEQ64B', 'z9nv5tpuW'
'VtyV8gXp1', 'ODmkNr22tB', 'U6Lw87k', 'IRpZLtNy8'
'rXVMxgC', 'gVKsych8Y', 'e7KJA9PQ', 'UDlXNdKC'
'yJzmSsZMFo', 'lDumW5oPS', '3kWzfmGtcW', 'a5M5fJ';
stre_0: '2';
stre_1: '2';
stre_2: '2';
stre_3: '2';
stre: 
'q65WK', '9kfg98rem'
'ECgj7J2c84', 'rharvgi'

'ynrRXmS1DX', 'mvlXXvAZ2L'
'l3aPrF8', 'ZaM6X'


'TUKjnjN4JL', 'fWHfkS'
'k4bRJE4IX', 'DGXhlSF'

'wS3NTBduDY', 'vz6bNOgQP'
'xDHoTrPh', 'ObSOv'.
```


## Structure with Structures and Structures Pointers
```C
typedef struct Cat {
	int age;
	char *name;
	double cute;
	struct Cat *next;
} Cat;

typedef struct Dog {
	int age;
	char *name;
	char *color;
	struct Dog *next;
} Dog;

typedef struct PetsSizes {
	int total;
	int cats;
	int dogs;
} PetsSizes;


typedef struct Pets {
	PetsSizes size;
	Cat *head_cats;
	Dog *head_dogs;
} Pets;
```

### To String 
```bash
TO_STRING:
Pets@55cf7c36f450
size: PetsSizes@55cf7c36f450;
head_cats: Cat@55cf7c3690e0;
head_dogs: Dog@55cf7c369030.
 |_ PetsSizes@55cf7c36f450
total: '8';
cats: '5';
dogs: '3'.
 |_ Cat@55cf7c3690e0
age: '10';
name: 'Sam';
cute: '0.500000';
next: Cat@55cf7c36d3a0.
 |_ Dog@55cf7c369030
age: '5';
name: 'Rain';
color: 'red';
next: Dog@55cf7c369550.
 |_ Cat@55cf7c36d3a0
age: '11';
name: 'Tom';
cute: '0.600000';
next: Cat@55cf7c36b2e0.
 |_ Dog@55cf7c369550
age: '7';
name: 'Blizzard';
color: 'white';
next: Dog@55cf7c36a5a0.
 |_ Cat@55cf7c36b2e0
age: '9';
name: 'Vid';
cute: '0.900000';
next: Cat@55cf7c36b290.
 |_ Dog@55cf7c36a5a0
age: '3';
name: 'Thunder';
color: 'blue';
next: Dog@0.
 |_ Cat@55cf7c36b290
age: '7';
name: 'Zip';
cute: '0.800000';
next: Cat@55cf7c369000.
 |_ Cat@55cf7c369000
age: '15';
name: 'Zap';
cute: '0.200000';
next: Cat@0.
```

### Json Encode
```bash
JSON_ENCODE:
"Pets@55cf7c36f450": {
	"size": PetsSizes@55cf7c36f450,
	"head_cats": Cat@55cf7c3690e0,
	"head_dogs": Dog@55cf7c369030
},
"PetsSizes@55cf7c36f450": {
	"total": 8,
	"cats": 5,
	"dogs": 3
},
"Cat@55cf7c3690e0": {
	"age": 10,
	"name": "U2Ft",
	"cute": 0.500000,
	"next": Cat@55cf7c36d3a0
},
"Dog@55cf7c369030": {
	"age": 5,
	"name": "UmFpbg==",
	"color": "cmVk",
	"next": Dog@55cf7c369550
},
"Cat@55cf7c36d3a0": {
	"age": 11,
	"name": "VG9t",
	"cute": 0.600000,
	"next": Cat@55cf7c36b2e0
},
"Dog@55cf7c369550": {
	"age": 7,
	"name": "QmxpenphcmQ=",
	"color": "d2hpdGU=",
	"next": Dog@55cf7c36a5a0
},
"Cat@55cf7c36b2e0": {
	"age": 9,
	"name": "Vmlk",
	"cute": 0.900000,
	"next": Cat@55cf7c36b290
},
"Dog@55cf7c36a5a0": {
	"age": 3,
	"name": "VGh1bmRlcg==",
	"color": "Ymx1ZQ==",
	"next": Dog@0
},
"Cat@55cf7c36b290": {
	"age": 7,
	"name": "Wmlw",
	"cute": 0.800000,
	"next": Cat@55cf7c369000
},
"Cat@55cf7c369000": {
	"age": 15,
	"name": "WmFw",
	"cute": 0.200000,
	"next": Cat@0
}
```

### Json Decode
```bash
JSON_DECODE:
Pets@55cf7c3a0250
size: PetsSizes@55cf7c3a0250;
head_cats: Cat@55cf7c3a2260;
head_dogs: Dog@55cf7c39c140.
 |_ PetsSizes@55cf7c3a0250
total: '8';
cats: '5';
dogs: '3'.
 |_ Cat@55cf7c3a2260
age: '10';
name: 'Sam';
cute: '0.500000';
next: Cat@55cf7c39c0d0.
 |_ Dog@55cf7c39c140
age: '5';
name: 'Rain';
color: 'red';
next: Dog@55cf7c368b90.
 |_ Cat@55cf7c39c0d0
age: '11';
name: 'Tom';
cute: '0.600000';
next: Cat@55cf7c38be60.
 |_ Dog@55cf7c368b90
age: '7';
name: 'Blizzard';
color: 'white';
next: Dog@55cf7c36afb0.
 |_ Cat@55cf7c38be60
age: '9';
name: 'Vid';
cute: '0.900000';
next: Cat@55cf7c36b020.
 |_ Dog@55cf7c36afb0
age: '3';
name: 'Thunder';
color: 'blue';
next: Dog@0.
 |_ Cat@55cf7c36b020
age: '7';
name: 'Zip';
cute: '0.800000';
next: Cat@55cf7c383650.
 |_ Cat@55cf7c383650
age: '15';
name: 'Zap';
cute: '0.200000';
next: Cat@0.
```

## Structures with Matrixes of Structures
```C
typedef struct Point {
	int x;
	int y;
} Point;

typedef struct Circle {
	Point c;
	int r;
} Circle;

typedef struct Rectangle {
	Point a;
	Point b;
} Rectangle;

typedef struct Triangle {
	Point a;
	Point b;
	Point c;
} Triangle;


typedef struct Figures {
	
	int circles_0;
	int circles_1;
	Circle ***circles;
	
	Triangle triangles[5][5];
	
	int rectangles_a;
	int rectangles_b;
	int rectangles_c;
	int rectangles_d;
	int rectangles_e;
	Rectangle*** rectangles[10][10][10];
} Figures;
```

### To String
```bash
TO_STRING:
Figures@55cf7c39e620
circles_0: '3';
circles_1: '4';
circles: 
Circle@55cf7c383120, Circle@55cf7c383630, Circle@55cf7c36b000, Circle@55cf7c38be90
Circle@55cf7c38beb0, Circle@55cf7c36a150, Circle@55cf7c36a170, Circle@55cf7c39e200
Circle@55cf7c39e220, Circle@55cf7c3a2290, Circle@55cf7c3a22b0, Circle@55cf7c36a5a0;
triangles: 
Triangle@55cf7c39e630, Triangle@55cf7c39e648, Triangle@55cf7c39e660, Triangle@55cf7c39e678, Triangle@55cf7c39e690
Triangle@55cf7c39e6a8, Triangle@55cf7c39e6c0, Triangle@55cf7c39e6d8, Triangle@55cf7c39e6f0, Triangle@55cf7c39e708
Triangle@55cf7c39e720, Triangle@55cf7c39e738, Triangle@55cf7c39e750, Triangle@55cf7c39e768, Triangle@55cf7c39e780
Triangle@55cf7c39e798, Triangle@55cf7c39e7b0, Triangle@55cf7c39e7c8, Triangle@55cf7c39e7e0, Triangle@55cf7c39e7f8
Triangle@55cf7c39e810, Triangle@55cf7c39e828, Triangle@55cf7c39e840, Triangle@55cf7c39e858, Triangle@55cf7c39e870;
rectangles_a: '2';
rectangles_b: '1';
rectangles_c: '2';
rectangles_d: '3';
rectangles_e: '3';
rectangles: 
Rectangle@55cf7c368b90, Rectangle@55cf7c371580, Rectangle@55cf7c3715a0
Rectangle@55cf7c387dc0, Rectangle@55cf7c387de0, Rectangle@55cf7c387e00
Rectangle@55cf7c37f9b0, Rectangle@55cf7c37f9d0, Rectangle@55cf7c3690e0

Rectangle@55cf7c39c100, Rectangle@55cf7c39c120, Rectangle@55cf7c39c140
Rectangle@55cf7c369000, Rectangle@55cf7c369020, Rectangle@55cf7c369040
Rectangle@55cf7c36b2b0, Rectangle@55cf7c36b2d0, Rectangle@55cf7c36b2f0



Rectangle@55cf7c383790, Rectangle@55cf7c3837b0, Rectangle@55cf7c3837d0
Rectangle@55cf7c36aba0, Rectangle@55cf7c36abc0, Rectangle@55cf7c36abe0
Rectangle@55cf7c36ac20, Rectangle@55cf7c36ac40, Rectangle@55cf7c36ac60

Rectangle@55cf7c36acc0, Rectangle@55cf7c36ace0, Rectangle@55cf7c36ad00
Rectangle@55cf7c36ad40, Rectangle@55cf7c36ad60, Rectangle@55cf7c36ad80
Rectangle@55cf7c36adc0, Rectangle@55cf7c36ade0, Rectangle@55cf7c36ae00.
 |_ Circle@55cf7c383120
c: Point@55cf7c383120;
r: '1'.
 |_ Circle@55cf7c383630
c: Point@55cf7c383630;
r: '4'.
 |_ Circle@55cf7c36b000
c: Point@55cf7c36b000;
r: '1'.
 |_ Circle@55cf7c38be90
c: Point@55cf7c38be90;
r: '0'.
 |_ Circle@55cf7c38beb0
c: Point@55cf7c38beb0;
r: '1'.
 |_ Circle@55cf7c36a150
c: Point@55cf7c36a150;
r: '4'.
 |_ Circle@55cf7c36a170
c: Point@55cf7c36a170;
r: '1'.
 |_ Circle@55cf7c39e200
c: Point@55cf7c39e200;
r: '1'.
 |_ Circle@55cf7c39e220
c: Point@55cf7c39e220;
r: '1'.
 |_ Circle@55cf7c3a2290
c: Point@55cf7c3a2290;
r: '4'.
 |_ Circle@55cf7c3a22b0
c: Point@55cf7c3a22b0;
r: '3'.
 |_ Circle@55cf7c36a5a0
c: Point@55cf7c36a5a0;
r: '1'.
 |_ Triangle@55cf7c39e630
a: Point@55cf7c39e630;
b: Point@55cf7c39e638;
c: Point@55cf7c39e640.
 |_ Triangle@55cf7c39e648
a: Point@55cf7c39e648;
b: Point@55cf7c39e650;
c: Point@55cf7c39e658.
 |_ Triangle@55cf7c39e660
a: Point@55cf7c39e660;
b: Point@55cf7c39e668;
c: Point@55cf7c39e670.
 |_ Triangle@55cf7c39e678
a: Point@55cf7c39e678;
b: Point@55cf7c39e680;
c: Point@55cf7c39e688.
 |_ Triangle@55cf7c39e690
a: Point@55cf7c39e690;
b: Point@55cf7c39e698;
c: Point@55cf7c39e6a0.
 |_ Triangle@55cf7c39e6a8
a: Point@55cf7c39e6a8;
b: Point@55cf7c39e6b0;
c: Point@55cf7c39e6b8.
 |_ Triangle@55cf7c39e6c0
a: Point@55cf7c39e6c0;
b: Point@55cf7c39e6c8;
c: Point@55cf7c39e6d0.
 |_ Triangle@55cf7c39e6d8
a: Point@55cf7c39e6d8;
b: Point@55cf7c39e6e0;
c: Point@55cf7c39e6e8.
 |_ Triangle@55cf7c39e6f0
a: Point@55cf7c39e6f0;
b: Point@55cf7c39e6f8;
c: Point@55cf7c39e700.
 |_ Triangle@55cf7c39e708
a: Point@55cf7c39e708;
b: Point@55cf7c39e710;
c: Point@55cf7c39e718.
 |_ Triangle@55cf7c39e720
a: Point@55cf7c39e720;
b: Point@55cf7c39e728;
c: Point@55cf7c39e730.
 |_ Triangle@55cf7c39e738
a: Point@55cf7c39e738;
b: Point@55cf7c39e740;
c: Point@55cf7c39e748.
 |_ Triangle@55cf7c39e750
a: Point@55cf7c39e750;
b: Point@55cf7c39e758;
c: Point@55cf7c39e760.
 |_ Triangle@55cf7c39e768
a: Point@55cf7c39e768;
b: Point@55cf7c39e770;
c: Point@55cf7c39e778.
 |_ Triangle@55cf7c39e780
a: Point@55cf7c39e780;
b: Point@55cf7c39e788;
c: Point@55cf7c39e790.
 |_ Triangle@55cf7c39e798
a: Point@55cf7c39e798;
b: Point@55cf7c39e7a0;
c: Point@55cf7c39e7a8.
 |_ Triangle@55cf7c39e7b0
a: Point@55cf7c39e7b0;
b: Point@55cf7c39e7b8;
c: Point@55cf7c39e7c0.
 |_ Triangle@55cf7c39e7c8
a: Point@55cf7c39e7c8;
b: Point@55cf7c39e7d0;
c: Point@55cf7c39e7d8.
 |_ Triangle@55cf7c39e7e0
a: Point@55cf7c39e7e0;
b: Point@55cf7c39e7e8;
c: Point@55cf7c39e7f0.
 |_ Triangle@55cf7c39e7f8
a: Point@55cf7c39e7f8;
b: Point@55cf7c39e800;
c: Point@55cf7c39e808.
 |_ Triangle@55cf7c39e810
a: Point@55cf7c39e810;
b: Point@55cf7c39e818;
c: Point@55cf7c39e820.
 |_ Triangle@55cf7c39e828
a: Point@55cf7c39e828;
b: Point@55cf7c39e830;
c: Point@55cf7c39e838.
 |_ Triangle@55cf7c39e840
a: Point@55cf7c39e840;
b: Point@55cf7c39e848;
c: Point@55cf7c39e850.
 |_ Triangle@55cf7c39e858
a: Point@55cf7c39e858;
b: Point@55cf7c39e860;
c: Point@55cf7c39e868.
 |_ Triangle@55cf7c39e870
a: Point@55cf7c39e870;
b: Point@55cf7c39e878;
c: Point@55cf7c39e880.
 |_ Rectangle@55cf7c368b90
a: Point@55cf7c368b90;
b: Point@55cf7c368b98.
 |_ Rectangle@55cf7c371580
a: Point@55cf7c371580;
b: Point@55cf7c371588.
 |_ Rectangle@55cf7c3715a0
a: Point@55cf7c3715a0;
b: Point@55cf7c3715a8.
 |_ Rectangle@55cf7c387dc0
a: Point@55cf7c387dc0;
b: Point@55cf7c387dc8.
 |_ Rectangle@55cf7c387de0
a: Point@55cf7c387de0;
b: Point@55cf7c387de8.
 |_ Rectangle@55cf7c387e00
a: Point@55cf7c387e00;
b: Point@55cf7c387e08.
 |_ Rectangle@55cf7c37f9b0
a: Point@55cf7c37f9b0;
b: Point@55cf7c37f9b8.
 |_ Rectangle@55cf7c37f9d0
a: Point@55cf7c37f9d0;
b: Point@55cf7c37f9d8.
 |_ Rectangle@55cf7c3690e0
a: Point@55cf7c3690e0;
b: Point@55cf7c3690e8.
 |_ Rectangle@55cf7c39c100
a: Point@55cf7c39c100;
b: Point@55cf7c39c108.
 |_ Rectangle@55cf7c39c120
a: Point@55cf7c39c120;
b: Point@55cf7c39c128.
 |_ Rectangle@55cf7c39c140
a: Point@55cf7c39c140;
b: Point@55cf7c39c148.
 |_ Rectangle@55cf7c369000
a: Point@55cf7c369000;
b: Point@55cf7c369008.
 |_ Rectangle@55cf7c369020
a: Point@55cf7c369020;
b: Point@55cf7c369028.
 |_ Rectangle@55cf7c369040
a: Point@55cf7c369040;
b: Point@55cf7c369048.
 |_ Rectangle@55cf7c36b2b0
a: Point@55cf7c36b2b0;
b: Point@55cf7c36b2b8.
 |_ Rectangle@55cf7c36b2d0
a: Point@55cf7c36b2d0;
b: Point@55cf7c36b2d8.
 |_ Rectangle@55cf7c36b2f0
a: Point@55cf7c36b2f0;
b: Point@55cf7c36b2f8.
 |_ Rectangle@55cf7c383790
a: Point@55cf7c383790;
b: Point@55cf7c383798.
 |_ Rectangle@55cf7c3837b0
a: Point@55cf7c3837b0;
b: Point@55cf7c3837b8.
 |_ Rectangle@55cf7c3837d0
a: Point@55cf7c3837d0;
b: Point@55cf7c3837d8.
 |_ Rectangle@55cf7c36aba0
a: Point@55cf7c36aba0;
b: Point@55cf7c36aba8.
 |_ Rectangle@55cf7c36abc0
a: Point@55cf7c36abc0;
b: Point@55cf7c36abc8.
 |_ Rectangle@55cf7c36abe0
a: Point@55cf7c36abe0;
b: Point@55cf7c36abe8.
 |_ Rectangle@55cf7c36ac20
a: Point@55cf7c36ac20;
b: Point@55cf7c36ac28.
 |_ Rectangle@55cf7c36ac40
a: Point@55cf7c36ac40;
b: Point@55cf7c36ac48.
 |_ Rectangle@55cf7c36ac60
a: Point@55cf7c36ac60;
b: Point@55cf7c36ac68.
 |_ Rectangle@55cf7c36acc0
a: Point@55cf7c36acc0;
b: Point@55cf7c36acc8.
 |_ Rectangle@55cf7c36ace0
a: Point@55cf7c36ace0;
b: Point@55cf7c36ace8.
 |_ Rectangle@55cf7c36ad00
a: Point@55cf7c36ad00;
b: Point@55cf7c36ad08.
 |_ Rectangle@55cf7c36ad40
a: Point@55cf7c36ad40;
b: Point@55cf7c36ad48.
 |_ Rectangle@55cf7c36ad60
a: Point@55cf7c36ad60;
b: Point@55cf7c36ad68.
 |_ Rectangle@55cf7c36ad80
a: Point@55cf7c36ad80;
b: Point@55cf7c36ad88.
 |_ Rectangle@55cf7c36adc0
a: Point@55cf7c36adc0;
b: Point@55cf7c36adc8.
 |_ Rectangle@55cf7c36ade0
a: Point@55cf7c36ade0;
b: Point@55cf7c36ade8.
 |_ Rectangle@55cf7c36ae00
a: Point@55cf7c36ae00;
b: Point@55cf7c36ae08.
 |_ Point@55cf7c383120
x: '2';
y: '19'.
 |_ Point@55cf7c383630
x: '-1';
y: '7'.
 |_ Point@55cf7c36b000
x: '-9';
y: '15'.
 |_ Point@55cf7c38be90
x: '14';
y: '22'.
 |_ Point@55cf7c38beb0
x: '10';
y: '-10'.
 |_ Point@55cf7c36a150
x: '2';
y: '9'.
 |_ Point@55cf7c36a170
x: '24';
y: '12'.
 |_ Point@55cf7c39e200
x: '-2';
y: '-3'.
 |_ Point@55cf7c39e220
x: '-5';
y: '7'.
 |_ Point@55cf7c3a2290
x: '-1';
y: '2'.
 |_ Point@55cf7c3a22b0
x: '-15';
y: '-20'.
 |_ Point@55cf7c36a5a0
x: '-24';
y: '6'.
 |_ Point@55cf7c39e630
x: '-8';
y: '23'.
 |_ Point@55cf7c39e638
x: '-7';
y: '13'.
 |_ Point@55cf7c39e640
x: '14';
y: '-9'.
 |_ Point@55cf7c39e648
x: '-12';
y: '0'.
 |_ Point@55cf7c39e650
x: '6';
y: '11'.
 |_ Point@55cf7c39e658
x: '-21';
y: '-8'.
 |_ Point@55cf7c39e660
x: '-25';
y: '-22'.
 |_ Point@55cf7c39e668
x: '-21';
y: '-22'.
 |_ Point@55cf7c39e670
x: '1';
y: '3'.
 |_ Point@55cf7c39e678
x: '-23';
y: '21'.
 |_ Point@55cf7c39e680
x: '-15';
y: '10'.
 |_ Point@55cf7c39e688
x: '-3';
y: '13'.
 |_ Point@55cf7c39e690
x: '9';
y: '9'.
 |_ Point@55cf7c39e698
x: '20';
y: '3'.
 |_ Point@55cf7c39e6a0
x: '10';
y: '3'.
 |_ Point@55cf7c39e6a8
x: '-19';
y: '-21'.
 |_ Point@55cf7c39e6b0
x: '1';
y: '-1'.
 |_ Point@55cf7c39e6b8
x: '17';
y: '-9'.
 |_ Point@55cf7c39e6c0
x: '17';
y: '-18'.
 |_ Point@55cf7c39e6c8
x: '18';
y: '0'.
 |_ Point@55cf7c39e6d0
x: '19';
y: '24'.
 |_ Point@55cf7c39e6d8
x: '17';
y: '21'.
 |_ Point@55cf7c39e6e0
x: '-23';
y: '22'.
 |_ Point@55cf7c39e6e8
x: '-25';
y: '5'.
 |_ Point@55cf7c39e6f0
x: '2';
y: '-23'.
 |_ Point@55cf7c39e6f8
x: '3';
y: '13'.
 |_ Point@55cf7c39e700
x: '12';
y: '-24'.
 |_ Point@55cf7c39e708
x: '3';
y: '-2'.
 |_ Point@55cf7c39e710
x: '10';
y: '-2'.
 |_ Point@55cf7c39e718
x: '-24';
y: '-2'.
 |_ Point@55cf7c39e720
x: '-22';
y: '-16'.
 |_ Point@55cf7c39e728
x: '4';
y: '5'.
 |_ Point@55cf7c39e730
x: '11';
y: '-3'.
 |_ Point@55cf7c39e738
x: '23';
y: '3'.
 |_ Point@55cf7c39e740
x: '4';
y: '18'.
 |_ Point@55cf7c39e748
x: '-21';
y: '0'.
 |_ Point@55cf7c39e750
x: '17';
y: '23'.
 |_ Point@55cf7c39e758
x: '-3';
y: '21'.
 |_ Point@55cf7c39e760
x: '20';
y: '-1'.
 |_ Point@55cf7c39e768
x: '1';
y: '-2'.
 |_ Point@55cf7c39e770
x: '3';
y: '-21'.
 |_ Point@55cf7c39e778
x: '-12';
y: '-8'.
 |_ Point@55cf7c39e780
x: '-18';
y: '16'.
 |_ Point@55cf7c39e788
x: '15';
y: '20'.
 |_ Point@55cf7c39e790
x: '-9';
y: '17'.
 |_ Point@55cf7c39e798
x: '-5';
y: '-6'.
 |_ Point@55cf7c39e7a0
x: '-22';
y: '24'.
 |_ Point@55cf7c39e7a8
x: '-24';
y: '14'.
 |_ Point@55cf7c39e7b0
x: '-4';
y: '24'.
 |_ Point@55cf7c39e7b8
x: '-5';
y: '-22'.
 |_ Point@55cf7c39e7c0
x: '19';
y: '1'.
 |_ Point@55cf7c39e7c8
x: '3';
y: '11'.
 |_ Point@55cf7c39e7d0
x: '-1';
y: '-23'.
 |_ Point@55cf7c39e7d8
x: '7';
y: '-3'.
 |_ Point@55cf7c39e7e0
x: '1';
y: '-15'.
 |_ Point@55cf7c39e7e8
x: '22';
y: '-21'.
 |_ Point@55cf7c39e7f0
x: '-10';
y: '-15'.
 |_ Point@55cf7c39e7f8
x: '-4';
y: '-1'.
 |_ Point@55cf7c39e800
x: '-24';
y: '-13'.
 |_ Point@55cf7c39e808
x: '-6';
y: '-6'.
 |_ Point@55cf7c39e810
x: '-19';
y: '14'.
 |_ Point@55cf7c39e818
x: '13';
y: '-16'.
 |_ Point@55cf7c39e820
x: '16';
y: '15'.
 |_ Point@55cf7c39e828
x: '-24';
y: '-13'.
 |_ Point@55cf7c39e830
x: '16';
y: '-2'.
 |_ Point@55cf7c39e838
x: '-8';
y: '11'.
 |_ Point@55cf7c39e840
x: '24';
y: '23'.
 |_ Point@55cf7c39e848
x: '-3';
y: '0'.
 |_ Point@55cf7c39e850
x: '-25';
y: '-18'.
 |_ Point@55cf7c39e858
x: '22';
y: '2'.
 |_ Point@55cf7c39e860
x: '-8';
y: '21'.
 |_ Point@55cf7c39e868
x: '6';
y: '9'.
 |_ Point@55cf7c39e870
x: '-19';
y: '-22'.
 |_ Point@55cf7c39e878
x: '-14';
y: '-16'.
 |_ Point@55cf7c39e880
x: '-8';
y: '5'.
 |_ Point@55cf7c368b90
x: '-3';
y: '-6'.
 |_ Point@55cf7c368b98
x: '0';
y: '0'.
 |_ Point@55cf7c371580
x: '-16';
y: '12'.
 |_ Point@55cf7c371588
x: '0';
y: '0'.
 |_ Point@55cf7c3715a0
x: '-15';
y: '22'.
 |_ Point@55cf7c3715a8
x: '0';
y: '0'.
 |_ Point@55cf7c387dc0
x: '20';
y: '-12'.
 |_ Point@55cf7c387dc8
x: '0';
y: '0'.
 |_ Point@55cf7c387de0
x: '-5';
y: '11'.
 |_ Point@55cf7c387de8
x: '0';
y: '0'.
 |_ Point@55cf7c387e00
x: '8';
y: '-19'.
 |_ Point@55cf7c387e08
x: '0';
y: '0'.
 |_ Point@55cf7c37f9b0
x: '-14';
y: '12'.
 |_ Point@55cf7c37f9b8
x: '0';
y: '0'.
 |_ Point@55cf7c37f9d0
x: '-6';
y: '6'.
 |_ Point@55cf7c37f9d8
x: '0';
y: '0'.
 |_ Point@55cf7c3690e0
x: '-25';
y: '12'.
 |_ Point@55cf7c3690e8
x: '0';
y: '0'.
 |_ Point@55cf7c39c100
x: '0';
y: '11'.
 |_ Point@55cf7c39c108
x: '0';
y: '0'.
 |_ Point@55cf7c39c120
x: '8';
y: '-23'.
 |_ Point@55cf7c39c128
x: '0';
y: '0'.
 |_ Point@55cf7c39c140
x: '-10';
y: '13'.
 |_ Point@55cf7c39c148
x: '0';
y: '0'.
 |_ Point@55cf7c369000
x: '1';
y: '23'.
 |_ Point@55cf7c369008
x: '0';
y: '0'.
 |_ Point@55cf7c369020
x: '-21';
y: '-22'.
 |_ Point@55cf7c369028
x: '0';
y: '0'.
 |_ Point@55cf7c369040
x: '15';
y: '-19'.
 |_ Point@55cf7c369048
x: '0';
y: '0'.
 |_ Point@55cf7c36b2b0
x: '12';
y: '23'.
 |_ Point@55cf7c36b2b8
x: '0';
y: '0'.
 |_ Point@55cf7c36b2d0
x: '10';
y: '-14'.
 |_ Point@55cf7c36b2d8
x: '0';
y: '0'.
 |_ Point@55cf7c36b2f0
x: '22';
y: '-8'.
 |_ Point@55cf7c36b2f8
x: '0';
y: '0'.
 |_ Point@55cf7c383790
x: '-5';
y: '24'.
 |_ Point@55cf7c383798
x: '0';
y: '0'.
 |_ Point@55cf7c3837b0
x: '12';
y: '9'.
 |_ Point@55cf7c3837b8
x: '0';
y: '0'.
 |_ Point@55cf7c3837d0
x: '7';
y: '-23'.
 |_ Point@55cf7c3837d8
x: '0';
y: '0'.
 |_ Point@55cf7c36aba0
x: '-18';
y: '5'.
 |_ Point@55cf7c36aba8
x: '0';
y: '0'.
 |_ Point@55cf7c36abc0
x: '11';
y: '-25'.
 |_ Point@55cf7c36abc8
x: '0';
y: '0'.
 |_ Point@55cf7c36abe0
x: '23';
y: '-10'.
 |_ Point@55cf7c36abe8
x: '0';
y: '0'.
 |_ Point@55cf7c36ac20
x: '2';
y: '-4'.
 |_ Point@55cf7c36ac28
x: '0';
y: '0'.
 |_ Point@55cf7c36ac40
x: '13';
y: '23'.
 |_ Point@55cf7c36ac48
x: '0';
y: '0'.
 |_ Point@55cf7c36ac60
x: '24';
y: '-10'.
 |_ Point@55cf7c36ac68
x: '0';
y: '0'.
 |_ Point@55cf7c36acc0
x: '24';
y: '-2'.
 |_ Point@55cf7c36acc8
x: '0';
y: '0'.
 |_ Point@55cf7c36ace0
x: '2';
y: '3'.
 |_ Point@55cf7c36ace8
x: '0';
y: '0'.
 |_ Point@55cf7c36ad00
x: '-17';
y: '3'.
 |_ Point@55cf7c36ad08
x: '0';
y: '0'.
 |_ Point@55cf7c36ad40
x: '5';
y: '22'.
 |_ Point@55cf7c36ad48
x: '0';
y: '0'.
 |_ Point@55cf7c36ad60
x: '-12';
y: '14'.
 |_ Point@55cf7c36ad68
x: '0';
y: '0'.
 |_ Point@55cf7c36ad80
x: '-13';
y: '-11'.
 |_ Point@55cf7c36ad88
x: '0';
y: '0'.
 |_ Point@55cf7c36adc0
x: '-11';
y: '-4'.
 |_ Point@55cf7c36adc8
x: '0';
y: '0'.
 |_ Point@55cf7c36ade0
x: '12';
y: '-14'.
 |_ Point@55cf7c36ade8
x: '0';
y: '0'.
 |_ Point@55cf7c36ae00
x: '11';
y: '-21'.
 |_ Point@55cf7c36ae08
x: '0';
y: '0'.
```

### Json Encode
```bash
JSON_ENCODE:
"Figures@55cf7c39e620": {
	"circles_0": 3,
	"circles_1": 4,
	"circles": [[Circle@55cf7c383120, Circle@55cf7c383630, Circle@55cf7c36b000, Circle@55cf7c38be90], [Circle@55cf7c38beb0, Circle@55cf7c36a150, Circle@55cf7c36a170, Circle@55cf7c39e200], [Circle@55cf7c39e220, Circle@55cf7c3a2290, Circle@55cf7c3a22b0, Circle@55cf7c36a5a0]],
	"triangles": [[Triangle@55cf7c39e630, Triangle@55cf7c39e648, Triangle@55cf7c39e660, Triangle@55cf7c39e678, Triangle@55cf7c39e690], [Triangle@55cf7c39e6a8, Triangle@55cf7c39e6c0, Triangle@55cf7c39e6d8, Triangle@55cf7c39e6f0, Triangle@55cf7c39e708], [Triangle@55cf7c39e720, Triangle@55cf7c39e738, Triangle@55cf7c39e750, Triangle@55cf7c39e768, Triangle@55cf7c39e780], [Triangle@55cf7c39e798, Triangle@55cf7c39e7b0, Triangle@55cf7c39e7c8, Triangle@55cf7c39e7e0, Triangle@55cf7c39e7f8], [Triangle@55cf7c39e810, Triangle@55cf7c39e828, Triangle@55cf7c39e840, Triangle@55cf7c39e858, Triangle@55cf7c39e870]],
	"rectangles_a": 2,
	"rectangles_b": 1,
	"rectangles_c": 2,
	"rectangles_d": 3,
	"rectangles_e": 3,
	"rectangles": [[[[[Rectangle@55cf7c368b90, Rectangle@55cf7c371580, Rectangle@55cf7c3715a0], [Rectangle@55cf7c387dc0, Rectangle@55cf7c387de0, Rectangle@55cf7c387e00], [Rectangle@55cf7c37f9b0, Rectangle@55cf7c37f9d0, Rectangle@55cf7c3690e0]], [[Rectangle@55cf7c39c100, Rectangle@55cf7c39c120, Rectangle@55cf7c39c140], [Rectangle@55cf7c369000, Rectangle@55cf7c369020, Rectangle@55cf7c369040], [Rectangle@55cf7c36b2b0, Rectangle@55cf7c36b2d0, Rectangle@55cf7c36b2f0]]]], [[[[Rectangle@55cf7c383790, Rectangle@55cf7c3837b0, Rectangle@55cf7c3837d0], [Rectangle@55cf7c36aba0, Rectangle@55cf7c36abc0, Rectangle@55cf7c36abe0], [Rectangle@55cf7c36ac20, Rectangle@55cf7c36ac40, Rectangle@55cf7c36ac60]], [[Rectangle@55cf7c36acc0, Rectangle@55cf7c36ace0, Rectangle@55cf7c36ad00], [Rectangle@55cf7c36ad40, Rectangle@55cf7c36ad60, Rectangle@55cf7c36ad80], [Rectangle@55cf7c36adc0, Rectangle@55cf7c36ade0, Rectangle@55cf7c36ae00]]]]]
},
"Circle@55cf7c383120": {
	"c": Point@55cf7c383120,
	"r": 1
},
"Circle@55cf7c383630": {
	"c": Point@55cf7c383630,
	"r": 4
},
"Circle@55cf7c36b000": {
	"c": Point@55cf7c36b000,
	"r": 1
},
"Circle@55cf7c38be90": {
	"c": Point@55cf7c38be90,
	"r": 0
},
"Circle@55cf7c38beb0": {
	"c": Point@55cf7c38beb0,
	"r": 1
},
"Circle@55cf7c36a150": {
	"c": Point@55cf7c36a150,
	"r": 4
},
"Circle@55cf7c36a170": {
	"c": Point@55cf7c36a170,
	"r": 1
},
"Circle@55cf7c39e200": {
	"c": Point@55cf7c39e200,
	"r": 1
},
"Circle@55cf7c39e220": {
	"c": Point@55cf7c39e220,
	"r": 1
},
"Circle@55cf7c3a2290": {
	"c": Point@55cf7c3a2290,
	"r": 4
},
"Circle@55cf7c3a22b0": {
	"c": Point@55cf7c3a22b0,
	"r": 3
},
"Circle@55cf7c36a5a0": {
	"c": Point@55cf7c36a5a0,
	"r": 1
},
"Triangle@55cf7c39e630": {
	"a": Point@55cf7c39e630,
	"b": Point@55cf7c39e638,
	"c": Point@55cf7c39e640
},
"Triangle@55cf7c39e648": {
	"a": Point@55cf7c39e648,
	"b": Point@55cf7c39e650,
	"c": Point@55cf7c39e658
},
"Triangle@55cf7c39e660": {
	"a": Point@55cf7c39e660,
	"b": Point@55cf7c39e668,
	"c": Point@55cf7c39e670
},
"Triangle@55cf7c39e678": {
	"a": Point@55cf7c39e678,
	"b": Point@55cf7c39e680,
	"c": Point@55cf7c39e688
},
"Triangle@55cf7c39e690": {
	"a": Point@55cf7c39e690,
	"b": Point@55cf7c39e698,
	"c": Point@55cf7c39e6a0
},
"Triangle@55cf7c39e6a8": {
	"a": Point@55cf7c39e6a8,
	"b": Point@55cf7c39e6b0,
	"c": Point@55cf7c39e6b8
},
"Triangle@55cf7c39e6c0": {
	"a": Point@55cf7c39e6c0,
	"b": Point@55cf7c39e6c8,
	"c": Point@55cf7c39e6d0
},
"Triangle@55cf7c39e6d8": {
	"a": Point@55cf7c39e6d8,
	"b": Point@55cf7c39e6e0,
	"c": Point@55cf7c39e6e8
},
"Triangle@55cf7c39e6f0": {
	"a": Point@55cf7c39e6f0,
	"b": Point@55cf7c39e6f8,
	"c": Point@55cf7c39e700
},
"Triangle@55cf7c39e708": {
	"a": Point@55cf7c39e708,
	"b": Point@55cf7c39e710,
	"c": Point@55cf7c39e718
},
"Triangle@55cf7c39e720": {
	"a": Point@55cf7c39e720,
	"b": Point@55cf7c39e728,
	"c": Point@55cf7c39e730
},
"Triangle@55cf7c39e738": {
	"a": Point@55cf7c39e738,
	"b": Point@55cf7c39e740,
	"c": Point@55cf7c39e748
},
"Triangle@55cf7c39e750": {
	"a": Point@55cf7c39e750,
	"b": Point@55cf7c39e758,
	"c": Point@55cf7c39e760
},
"Triangle@55cf7c39e768": {
	"a": Point@55cf7c39e768,
	"b": Point@55cf7c39e770,
	"c": Point@55cf7c39e778
},
"Triangle@55cf7c39e780": {
	"a": Point@55cf7c39e780,
	"b": Point@55cf7c39e788,
	"c": Point@55cf7c39e790
},
"Triangle@55cf7c39e798": {
	"a": Point@55cf7c39e798,
	"b": Point@55cf7c39e7a0,
	"c": Point@55cf7c39e7a8
},
"Triangle@55cf7c39e7b0": {
	"a": Point@55cf7c39e7b0,
	"b": Point@55cf7c39e7b8,
	"c": Point@55cf7c39e7c0
},
"Triangle@55cf7c39e7c8": {
	"a": Point@55cf7c39e7c8,
	"b": Point@55cf7c39e7d0,
	"c": Point@55cf7c39e7d8
},
"Triangle@55cf7c39e7e0": {
	"a": Point@55cf7c39e7e0,
	"b": Point@55cf7c39e7e8,
	"c": Point@55cf7c39e7f0
},
"Triangle@55cf7c39e7f8": {
	"a": Point@55cf7c39e7f8,
	"b": Point@55cf7c39e800,
	"c": Point@55cf7c39e808
},
"Triangle@55cf7c39e810": {
	"a": Point@55cf7c39e810,
	"b": Point@55cf7c39e818,
	"c": Point@55cf7c39e820
},
"Triangle@55cf7c39e828": {
	"a": Point@55cf7c39e828,
	"b": Point@55cf7c39e830,
	"c": Point@55cf7c39e838
},
"Triangle@55cf7c39e840": {
	"a": Point@55cf7c39e840,
	"b": Point@55cf7c39e848,
	"c": Point@55cf7c39e850
},
"Triangle@55cf7c39e858": {
	"a": Point@55cf7c39e858,
	"b": Point@55cf7c39e860,
	"c": Point@55cf7c39e868
},
"Triangle@55cf7c39e870": {
	"a": Point@55cf7c39e870,
	"b": Point@55cf7c39e878,
	"c": Point@55cf7c39e880
},
"Rectangle@55cf7c368b90": {
	"a": Point@55cf7c368b90,
	"b": Point@55cf7c368b98
},
"Rectangle@55cf7c371580": {
	"a": Point@55cf7c371580,
	"b": Point@55cf7c371588
},
"Rectangle@55cf7c3715a0": {
	"a": Point@55cf7c3715a0,
	"b": Point@55cf7c3715a8
},
"Rectangle@55cf7c387dc0": {
	"a": Point@55cf7c387dc0,
	"b": Point@55cf7c387dc8
},
"Rectangle@55cf7c387de0": {
	"a": Point@55cf7c387de0,
	"b": Point@55cf7c387de8
},
"Rectangle@55cf7c387e00": {
	"a": Point@55cf7c387e00,
	"b": Point@55cf7c387e08
},
"Rectangle@55cf7c37f9b0": {
	"a": Point@55cf7c37f9b0,
	"b": Point@55cf7c37f9b8
},
"Rectangle@55cf7c37f9d0": {
	"a": Point@55cf7c37f9d0,
	"b": Point@55cf7c37f9d8
},
"Rectangle@55cf7c3690e0": {
	"a": Point@55cf7c3690e0,
	"b": Point@55cf7c3690e8
},
"Rectangle@55cf7c39c100": {
	"a": Point@55cf7c39c100,
	"b": Point@55cf7c39c108
},
"Rectangle@55cf7c39c120": {
	"a": Point@55cf7c39c120,
	"b": Point@55cf7c39c128
},
"Rectangle@55cf7c39c140": {
	"a": Point@55cf7c39c140,
	"b": Point@55cf7c39c148
},
"Rectangle@55cf7c369000": {
	"a": Point@55cf7c369000,
	"b": Point@55cf7c369008
},
"Rectangle@55cf7c369020": {
	"a": Point@55cf7c369020,
	"b": Point@55cf7c369028
},
"Rectangle@55cf7c369040": {
	"a": Point@55cf7c369040,
	"b": Point@55cf7c369048
},
"Rectangle@55cf7c36b2b0": {
	"a": Point@55cf7c36b2b0,
	"b": Point@55cf7c36b2b8
},
"Rectangle@55cf7c36b2d0": {
	"a": Point@55cf7c36b2d0,
	"b": Point@55cf7c36b2d8
},
"Rectangle@55cf7c36b2f0": {
	"a": Point@55cf7c36b2f0,
	"b": Point@55cf7c36b2f8
},
"Rectangle@55cf7c383790": {
	"a": Point@55cf7c383790,
	"b": Point@55cf7c383798
},
"Rectangle@55cf7c3837b0": {
	"a": Point@55cf7c3837b0,
	"b": Point@55cf7c3837b8
},
"Rectangle@55cf7c3837d0": {
	"a": Point@55cf7c3837d0,
	"b": Point@55cf7c3837d8
},
"Rectangle@55cf7c36aba0": {
	"a": Point@55cf7c36aba0,
	"b": Point@55cf7c36aba8
},
"Rectangle@55cf7c36abc0": {
	"a": Point@55cf7c36abc0,
	"b": Point@55cf7c36abc8
},
"Rectangle@55cf7c36abe0": {
	"a": Point@55cf7c36abe0,
	"b": Point@55cf7c36abe8
},
"Rectangle@55cf7c36ac20": {
	"a": Point@55cf7c36ac20,
	"b": Point@55cf7c36ac28
},
"Rectangle@55cf7c36ac40": {
	"a": Point@55cf7c36ac40,
	"b": Point@55cf7c36ac48
},
"Rectangle@55cf7c36ac60": {
	"a": Point@55cf7c36ac60,
	"b": Point@55cf7c36ac68
},
"Rectangle@55cf7c36acc0": {
	"a": Point@55cf7c36acc0,
	"b": Point@55cf7c36acc8
},
"Rectangle@55cf7c36ace0": {
	"a": Point@55cf7c36ace0,
	"b": Point@55cf7c36ace8
},
"Rectangle@55cf7c36ad00": {
	"a": Point@55cf7c36ad00,
	"b": Point@55cf7c36ad08
},
"Rectangle@55cf7c36ad40": {
	"a": Point@55cf7c36ad40,
	"b": Point@55cf7c36ad48
},
"Rectangle@55cf7c36ad60": {
	"a": Point@55cf7c36ad60,
	"b": Point@55cf7c36ad68
},
"Rectangle@55cf7c36ad80": {
	"a": Point@55cf7c36ad80,
	"b": Point@55cf7c36ad88
},
"Rectangle@55cf7c36adc0": {
	"a": Point@55cf7c36adc0,
	"b": Point@55cf7c36adc8
},
"Rectangle@55cf7c36ade0": {
	"a": Point@55cf7c36ade0,
	"b": Point@55cf7c36ade8
},
"Rectangle@55cf7c36ae00": {
	"a": Point@55cf7c36ae00,
	"b": Point@55cf7c36ae08
},
"Point@55cf7c383120": {
	"x": 2,
	"y": 19
},
"Point@55cf7c383630": {
	"x": -1,
	"y": 7
},
"Point@55cf7c36b000": {
	"x": -9,
	"y": 15
},
"Point@55cf7c38be90": {
	"x": 14,
	"y": 22
},
"Point@55cf7c38beb0": {
	"x": 10,
	"y": -10
},
"Point@55cf7c36a150": {
	"x": 2,
	"y": 9
},
"Point@55cf7c36a170": {
	"x": 24,
	"y": 12
},
"Point@55cf7c39e200": {
	"x": -2,
	"y": -3
},
"Point@55cf7c39e220": {
	"x": -5,
	"y": 7
},
"Point@55cf7c3a2290": {
	"x": -1,
	"y": 2
},
"Point@55cf7c3a22b0": {
	"x": -15,
	"y": -20
},
"Point@55cf7c36a5a0": {
	"x": -24,
	"y": 6
},
"Point@55cf7c39e630": {
	"x": -8,
	"y": 23
},
"Point@55cf7c39e638": {
	"x": -7,
	"y": 13
},
"Point@55cf7c39e640": {
	"x": 14,
	"y": -9
},
"Point@55cf7c39e648": {
	"x": -12,
	"y": 0
},
"Point@55cf7c39e650": {
	"x": 6,
	"y": 11
},
"Point@55cf7c39e658": {
	"x": -21,
	"y": -8
},
"Point@55cf7c39e660": {
	"x": -25,
	"y": -22
},
"Point@55cf7c39e668": {
	"x": -21,
	"y": -22
},
"Point@55cf7c39e670": {
	"x": 1,
	"y": 3
},
"Point@55cf7c39e678": {
	"x": -23,
	"y": 21
},
"Point@55cf7c39e680": {
	"x": -15,
	"y": 10
},
"Point@55cf7c39e688": {
	"x": -3,
	"y": 13
},
"Point@55cf7c39e690": {
	"x": 9,
	"y": 9
},
"Point@55cf7c39e698": {
	"x": 20,
	"y": 3
},
"Point@55cf7c39e6a0": {
	"x": 10,
	"y": 3
},
"Point@55cf7c39e6a8": {
	"x": -19,
	"y": -21
},
"Point@55cf7c39e6b0": {
	"x": 1,
	"y": -1
},
"Point@55cf7c39e6b8": {
	"x": 17,
	"y": -9
},
"Point@55cf7c39e6c0": {
	"x": 17,
	"y": -18
},
"Point@55cf7c39e6c8": {
	"x": 18,
	"y": 0
},
"Point@55cf7c39e6d0": {
	"x": 19,
	"y": 24
},
"Point@55cf7c39e6d8": {
	"x": 17,
	"y": 21
},
"Point@55cf7c39e6e0": {
	"x": -23,
	"y": 22
},
"Point@55cf7c39e6e8": {
	"x": -25,
	"y": 5
},
"Point@55cf7c39e6f0": {
	"x": 2,
	"y": -23
},
"Point@55cf7c39e6f8": {
	"x": 3,
	"y": 13
},
"Point@55cf7c39e700": {
	"x": 12,
	"y": -24
},
"Point@55cf7c39e708": {
	"x": 3,
	"y": -2
},
"Point@55cf7c39e710": {
	"x": 10,
	"y": -2
},
"Point@55cf7c39e718": {
	"x": -24,
	"y": -2
},
"Point@55cf7c39e720": {
	"x": -22,
	"y": -16
},
"Point@55cf7c39e728": {
	"x": 4,
	"y": 5
},
"Point@55cf7c39e730": {
	"x": 11,
	"y": -3
},
"Point@55cf7c39e738": {
	"x": 23,
	"y": 3
},
"Point@55cf7c39e740": {
	"x": 4,
	"y": 18
},
"Point@55cf7c39e748": {
	"x": -21,
	"y": 0
},
"Point@55cf7c39e750": {
	"x": 17,
	"y": 23
},
"Point@55cf7c39e758": {
	"x": -3,
	"y": 21
},
"Point@55cf7c39e760": {
	"x": 20,
	"y": -1
},
"Point@55cf7c39e768": {
	"x": 1,
	"y": -2
},
"Point@55cf7c39e770": {
	"x": 3,
	"y": -21
},
"Point@55cf7c39e778": {
	"x": -12,
	"y": -8
},
"Point@55cf7c39e780": {
	"x": -18,
	"y": 16
},
"Point@55cf7c39e788": {
	"x": 15,
	"y": 20
},
"Point@55cf7c39e790": {
	"x": -9,
	"y": 17
},
"Point@55cf7c39e798": {
	"x": -5,
	"y": -6
},
"Point@55cf7c39e7a0": {
	"x": -22,
	"y": 24
},
"Point@55cf7c39e7a8": {
	"x": -24,
	"y": 14
},
"Point@55cf7c39e7b0": {
	"x": -4,
	"y": 24
},
"Point@55cf7c39e7b8": {
	"x": -5,
	"y": -22
},
"Point@55cf7c39e7c0": {
	"x": 19,
	"y": 1
},
"Point@55cf7c39e7c8": {
	"x": 3,
	"y": 11
},
"Point@55cf7c39e7d0": {
	"x": -1,
	"y": -23
},
"Point@55cf7c39e7d8": {
	"x": 7,
	"y": -3
},
"Point@55cf7c39e7e0": {
	"x": 1,
	"y": -15
},
"Point@55cf7c39e7e8": {
	"x": 22,
	"y": -21
},
"Point@55cf7c39e7f0": {
	"x": -10,
	"y": -15
},
"Point@55cf7c39e7f8": {
	"x": -4,
	"y": -1
},
"Point@55cf7c39e800": {
	"x": -24,
	"y": -13
},
"Point@55cf7c39e808": {
	"x": -6,
	"y": -6
},
"Point@55cf7c39e810": {
	"x": -19,
	"y": 14
},
"Point@55cf7c39e818": {
	"x": 13,
	"y": -16
},
"Point@55cf7c39e820": {
	"x": 16,
	"y": 15
},
"Point@55cf7c39e828": {
	"x": -24,
	"y": -13
},
"Point@55cf7c39e830": {
	"x": 16,
	"y": -2
},
"Point@55cf7c39e838": {
	"x": -8,
	"y": 11
},
"Point@55cf7c39e840": {
	"x": 24,
	"y": 23
},
"Point@55cf7c39e848": {
	"x": -3,
	"y": 0
},
"Point@55cf7c39e850": {
	"x": -25,
	"y": -18
},
"Point@55cf7c39e858": {
	"x": 22,
	"y": 2
},
"Point@55cf7c39e860": {
	"x": -8,
	"y": 21
},
"Point@55cf7c39e868": {
	"x": 6,
	"y": 9
},
"Point@55cf7c39e870": {
	"x": -19,
	"y": -22
},
"Point@55cf7c39e878": {
	"x": -14,
	"y": -16
},
"Point@55cf7c39e880": {
	"x": -8,
	"y": 5
},
"Point@55cf7c368b90": {
	"x": -3,
	"y": -6
},
"Point@55cf7c368b98": {
	"x": 0,
	"y": 0
},
"Point@55cf7c371580": {
	"x": -16,
	"y": 12
},
"Point@55cf7c371588": {
	"x": 0,
	"y": 0
},
"Point@55cf7c3715a0": {
	"x": -15,
	"y": 22
},
"Point@55cf7c3715a8": {
	"x": 0,
	"y": 0
},
"Point@55cf7c387dc0": {
	"x": 20,
	"y": -12
},
"Point@55cf7c387dc8": {
	"x": 0,
	"y": 0
},
"Point@55cf7c387de0": {
	"x": -5,
	"y": 11
},
"Point@55cf7c387de8": {
	"x": 0,
	"y": 0
},
"Point@55cf7c387e00": {
	"x": 8,
	"y": -19
},
"Point@55cf7c387e08": {
	"x": 0,
	"y": 0
},
"Point@55cf7c37f9b0": {
	"x": -14,
	"y": 12
},
"Point@55cf7c37f9b8": {
	"x": 0,
	"y": 0
},
"Point@55cf7c37f9d0": {
	"x": -6,
	"y": 6
},
"Point@55cf7c37f9d8": {
	"x": 0,
	"y": 0
},
"Point@55cf7c3690e0": {
	"x": -25,
	"y": 12
},
"Point@55cf7c3690e8": {
	"x": 0,
	"y": 0
},
"Point@55cf7c39c100": {
	"x": 0,
	"y": 11
},
"Point@55cf7c39c108": {
	"x": 0,
	"y": 0
},
"Point@55cf7c39c120": {
	"x": 8,
	"y": -23
},
"Point@55cf7c39c128": {
	"x": 0,
	"y": 0
},
"Point@55cf7c39c140": {
	"x": -10,
	"y": 13
},
"Point@55cf7c39c148": {
	"x": 0,
	"y": 0
},
"Point@55cf7c369000": {
	"x": 1,
	"y": 23
},
"Point@55cf7c369008": {
	"x": 0,
	"y": 0
},
"Point@55cf7c369020": {
	"x": -21,
	"y": -22
},
"Point@55cf7c369028": {
	"x": 0,
	"y": 0
},
"Point@55cf7c369040": {
	"x": 15,
	"y": -19
},
"Point@55cf7c369048": {
	"x": 0,
	"y": 0
},
"Point@55cf7c36b2b0": {
	"x": 12,
	"y": 23
},
"Point@55cf7c36b2b8": {
	"x": 0,
	"y": 0
},
"Point@55cf7c36b2d0": {
	"x": 10,
	"y": -14
},
"Point@55cf7c36b2d8": {
	"x": 0,
	"y": 0
},
"Point@55cf7c36b2f0": {
	"x": 22,
	"y": -8
},
"Point@55cf7c36b2f8": {
	"x": 0,
	"y": 0
},
"Point@55cf7c383790": {
	"x": -5,
	"y": 24
},
"Point@55cf7c383798": {
	"x": 0,
	"y": 0
},
"Point@55cf7c3837b0": {
	"x": 12,
	"y": 9
},
"Point@55cf7c3837b8": {
	"x": 0,
	"y": 0
},
"Point@55cf7c3837d0": {
	"x": 7,
	"y": -23
},
"Point@55cf7c3837d8": {
	"x": 0,
	"y": 0
},
"Point@55cf7c36aba0": {
	"x": -18,
	"y": 5
},
"Point@55cf7c36aba8": {
	"x": 0,
	"y": 0
},
"Point@55cf7c36abc0": {
	"x": 11,
	"y": -25
},
"Point@55cf7c36abc8": {
	"x": 0,
	"y": 0
},
"Point@55cf7c36abe0": {
	"x": 23,
	"y": -10
},
"Point@55cf7c36abe8": {
	"x": 0,
	"y": 0
},
"Point@55cf7c36ac20": {
	"x": 2,
	"y": -4
},
"Point@55cf7c36ac28": {
	"x": 0,
	"y": 0
},
"Point@55cf7c36ac40": {
	"x": 13,
	"y": 23
},
"Point@55cf7c36ac48": {
	"x": 0,
	"y": 0
},
"Point@55cf7c36ac60": {
	"x": 24,
	"y": -10
},
"Point@55cf7c36ac68": {
	"x": 0,
	"y": 0
},
"Point@55cf7c36acc0": {
	"x": 24,
	"y": -2
},
"Point@55cf7c36acc8": {
	"x": 0,
	"y": 0
},
"Point@55cf7c36ace0": {
	"x": 2,
	"y": 3
},
"Point@55cf7c36ace8": {
	"x": 0,
	"y": 0
},
"Point@55cf7c36ad00": {
	"x": -17,
	"y": 3
},
"Point@55cf7c36ad08": {
	"x": 0,
	"y": 0
},
"Point@55cf7c36ad40": {
	"x": 5,
	"y": 22
},
"Point@55cf7c36ad48": {
	"x": 0,
	"y": 0
},
"Point@55cf7c36ad60": {
	"x": -12,
	"y": 14
},
"Point@55cf7c36ad68": {
	"x": 0,
	"y": 0
},
"Point@55cf7c36ad80": {
	"x": -13,
	"y": -11
},
"Point@55cf7c36ad88": {
	"x": 0,
	"y": 0
},
"Point@55cf7c36adc0": {
	"x": -11,
	"y": -4
},
"Point@55cf7c36adc8": {
	"x": 0,
	"y": 0
},
"Point@55cf7c36ade0": {
	"x": 12,
	"y": -14
},
"Point@55cf7c36ade8": {
	"x": 0,
	"y": 0
},
"Point@55cf7c36ae00": {
	"x": 11,
	"y": -21
},
"Point@55cf7c36ae08": {
	"x": 0,
	"y": 0
}
```

### Json Decode
```bash
JSON_DECODE:
Figures@55cf7c3a6510
circles_0: '3';
circles_1: '4';
circles: 
Circle@55cf7c3afbc0, Circle@55cf7c3afb80, Circle@55cf7c3afb20, Circle@55cf7c383590
Circle@55cf7c383610, Circle@55cf7c36aeb0, Circle@55cf7c36af30, Circle@55cf7c36afb0
Circle@55cf7c3a8710, Circle@55cf7c3a8790, Circle@55cf7c3a8810, Circle@55cf7c3a8890;
triangles: 
Triangle@55cf7c3a6520, Triangle@55cf7c3a6538, Triangle@55cf7c3a6550, Triangle@55cf7c3a6568, Triangle@55cf7c3a6580
Triangle@55cf7c3a6598, Triangle@55cf7c3a65b0, Triangle@55cf7c3a65c8, Triangle@55cf7c3a65e0, Triangle@55cf7c3a65f8
Triangle@55cf7c3a6610, Triangle@55cf7c3a6628, Triangle@55cf7c3a6640, Triangle@55cf7c3a6658, Triangle@55cf7c3a6670
Triangle@55cf7c3a6688, Triangle@55cf7c3a66a0, Triangle@55cf7c3a66b8, Triangle@55cf7c3a66d0, Triangle@55cf7c3a66e8
Triangle@55cf7c3a6700, Triangle@55cf7c3a6718, Triangle@55cf7c3a6730, Triangle@55cf7c3a6748, Triangle@55cf7c3a6760;
rectangles_a: '2';
rectangles_b: '1';
rectangles_c: '2';
rectangles_d: '3';
rectangles_e: '3';
rectangles: 
Rectangle@55cf7c3a9700, Rectangle@55cf7c3a9780, Rectangle@55cf7c3a9800
Rectangle@55cf7c3a98a0, Rectangle@55cf7c3a9920, Rectangle@55cf7c3a99a0
Rectangle@55cf7c381c00, Rectangle@55cf7c381c80, Rectangle@55cf7c381d00

Rectangle@55cf7c3a8b70, Rectangle@55cf7c3a8bf0, Rectangle@55cf7c3a8c70
Rectangle@55cf7c3a8d10, Rectangle@55cf7c3a8d90, Rectangle@55cf7c3a8e10
Rectangle@55cf7c3a8eb0, Rectangle@55cf7c382190, Rectangle@55cf7c382210



Rectangle@55cf7c381dc0, Rectangle@55cf7c381e40, Rectangle@55cf7c381ec0
Rectangle@55cf7c381f60, Rectangle@55cf7c381fe0, Rectangle@55cf7c382060
Rectangle@55cf7c382100, Rectangle@55cf7c3826a0, Rectangle@55cf7c382720

Rectangle@55cf7c3822d0, Rectangle@55cf7c382350, Rectangle@55cf7c3823d0
Rectangle@55cf7c382470, Rectangle@55cf7c3824f0, Rectangle@55cf7c382570
Rectangle@55cf7c382610, Rectangle@55cf7c382bb0, Rectangle@55cf7c382c30.
 |_ Circle@55cf7c3afbc0
c: Point@55cf7c3afbc0;
r: '1'.
 |_ Circle@55cf7c3afb80
c: Point@55cf7c3afb80;
r: '4'.
 |_ Circle@55cf7c3afb20
c: Point@55cf7c3afb20;
r: '1'.
 |_ Circle@55cf7c383590
c: Point@55cf7c383590;
r: '0'.
 |_ Circle@55cf7c383610
c: Point@55cf7c383610;
r: '1'.
 |_ Circle@55cf7c36aeb0
c: Point@55cf7c36aeb0;
r: '4'.
 |_ Circle@55cf7c36af30
c: Point@55cf7c36af30;
r: '1'.
 |_ Circle@55cf7c36afb0
c: Point@55cf7c36afb0;
r: '1'.
 |_ Circle@55cf7c3a8710
c: Point@55cf7c3a8710;
r: '1'.
 |_ Circle@55cf7c3a8790
c: Point@55cf7c3a8790;
r: '4'.
 |_ Circle@55cf7c3a8810
c: Point@55cf7c3a8810;
r: '3'.
 |_ Circle@55cf7c3a8890
c: Point@55cf7c3a8890;
r: '1'.
 |_ Triangle@55cf7c3a6520
a: Point@55cf7c3a6520;
b: Point@55cf7c3a6528;
c: Point@55cf7c3a6530.
 |_ Triangle@55cf7c3a6538
a: Point@55cf7c3a6538;
b: Point@55cf7c3a6540;
c: Point@55cf7c3a6548.
 |_ Triangle@55cf7c3a6550
a: Point@55cf7c3a6550;
b: Point@55cf7c3a6558;
c: Point@55cf7c3a6560.
 |_ Triangle@55cf7c3a6568
a: Point@55cf7c3a6568;
b: Point@55cf7c3a6570;
c: Point@55cf7c3a6578.
 |_ Triangle@55cf7c3a6580
a: Point@55cf7c3a6580;
b: Point@55cf7c3a6588;
c: Point@55cf7c3a6590.
 |_ Triangle@55cf7c3a6598
a: Point@55cf7c3a6598;
b: Point@55cf7c3a65a0;
c: Point@55cf7c3a65a8.
 |_ Triangle@55cf7c3a65b0
a: Point@55cf7c3a65b0;
b: Point@55cf7c3a65b8;
c: Point@55cf7c3a65c0.
 |_ Triangle@55cf7c3a65c8
a: Point@55cf7c3a65c8;
b: Point@55cf7c3a65d0;
c: Point@55cf7c3a65d8.
 |_ Triangle@55cf7c3a65e0
a: Point@55cf7c3a65e0;
b: Point@55cf7c3a65e8;
c: Point@55cf7c3a65f0.
 |_ Triangle@55cf7c3a65f8
a: Point@55cf7c3a65f8;
b: Point@55cf7c3a6600;
c: Point@55cf7c3a6608.
 |_ Triangle@55cf7c3a6610
a: Point@55cf7c3a6610;
b: Point@55cf7c3a6618;
c: Point@55cf7c3a6620.
 |_ Triangle@55cf7c3a6628
a: Point@55cf7c3a6628;
b: Point@55cf7c3a6630;
c: Point@55cf7c3a6638.
 |_ Triangle@55cf7c3a6640
a: Point@55cf7c3a6640;
b: Point@55cf7c3a6648;
c: Point@55cf7c3a6650.
 |_ Triangle@55cf7c3a6658
a: Point@55cf7c3a6658;
b: Point@55cf7c3a6660;
c: Point@55cf7c3a6668.
 |_ Triangle@55cf7c3a6670
a: Point@55cf7c3a6670;
b: Point@55cf7c3a6678;
c: Point@55cf7c3a6680.
 |_ Triangle@55cf7c3a6688
a: Point@55cf7c3a6688;
b: Point@55cf7c3a6690;
c: Point@55cf7c3a6698.
 |_ Triangle@55cf7c3a66a0
a: Point@55cf7c3a66a0;
b: Point@55cf7c3a66a8;
c: Point@55cf7c3a66b0.
 |_ Triangle@55cf7c3a66b8
a: Point@55cf7c3a66b8;
b: Point@55cf7c3a66c0;
c: Point@55cf7c3a66c8.
 |_ Triangle@55cf7c3a66d0
a: Point@55cf7c3a66d0;
b: Point@55cf7c3a66d8;
c: Point@55cf7c3a66e0.
 |_ Triangle@55cf7c3a66e8
a: Point@55cf7c3a66e8;
b: Point@55cf7c3a66f0;
c: Point@55cf7c3a66f8.
 |_ Triangle@55cf7c3a6700
a: Point@55cf7c3a6700;
b: Point@55cf7c3a6708;
c: Point@55cf7c3a6710.
 |_ Triangle@55cf7c3a6718
a: Point@55cf7c3a6718;
b: Point@55cf7c3a6720;
c: Point@55cf7c3a6728.
 |_ Triangle@55cf7c3a6730
a: Point@55cf7c3a6730;
b: Point@55cf7c3a6738;
c: Point@55cf7c3a6740.
 |_ Triangle@55cf7c3a6748
a: Point@55cf7c3a6748;
b: Point@55cf7c3a6750;
c: Point@55cf7c3a6758.
 |_ Triangle@55cf7c3a6760
a: Point@55cf7c3a6760;
b: Point@55cf7c3a6768;
c: Point@55cf7c3a6770.
 |_ Rectangle@55cf7c3a9700
a: Point@55cf7c3a9700;
b: Point@55cf7c3a9708.
 |_ Rectangle@55cf7c3a9780
a: Point@55cf7c3a9780;
b: Point@55cf7c3a9788.
 |_ Rectangle@55cf7c3a9800
a: Point@55cf7c3a9800;
b: Point@55cf7c3a9808.
 |_ Rectangle@55cf7c3a98a0
a: Point@55cf7c3a98a0;
b: Point@55cf7c3a98a8.
 |_ Rectangle@55cf7c3a9920
a: Point@55cf7c3a9920;
b: Point@55cf7c3a9928.
 |_ Rectangle@55cf7c3a99a0
a: Point@55cf7c3a99a0;
b: Point@55cf7c3a99a8.
 |_ Rectangle@55cf7c381c00
a: Point@55cf7c381c00;
b: Point@55cf7c381c08.
 |_ Rectangle@55cf7c381c80
a: Point@55cf7c381c80;
b: Point@55cf7c381c88.
 |_ Rectangle@55cf7c381d00
a: Point@55cf7c381d00;
b: Point@55cf7c381d08.
 |_ Rectangle@55cf7c3a8b70
a: Point@55cf7c3a8b70;
b: Point@55cf7c3a8b78.
 |_ Rectangle@55cf7c3a8bf0
a: Point@55cf7c3a8bf0;
b: Point@55cf7c3a8bf8.
 |_ Rectangle@55cf7c3a8c70
a: Point@55cf7c3a8c70;
b: Point@55cf7c3a8c78.
 |_ Rectangle@55cf7c3a8d10
a: Point@55cf7c3a8d10;
b: Point@55cf7c3a8d18.
 |_ Rectangle@55cf7c3a8d90
a: Point@55cf7c3a8d90;
b: Point@55cf7c3a8d98.
 |_ Rectangle@55cf7c3a8e10
a: Point@55cf7c3a8e10;
b: Point@55cf7c3a8e18.
 |_ Rectangle@55cf7c3a8eb0
a: Point@55cf7c3a8eb0;
b: Point@55cf7c3a8eb8.
 |_ Rectangle@55cf7c382190
a: Point@55cf7c382190;
b: Point@55cf7c382198.
 |_ Rectangle@55cf7c382210
a: Point@55cf7c382210;
b: Point@55cf7c382218.
 |_ Rectangle@55cf7c381dc0
a: Point@55cf7c381dc0;
b: Point@55cf7c381dc8.
 |_ Rectangle@55cf7c381e40
a: Point@55cf7c381e40;
b: Point@55cf7c381e48.
 |_ Rectangle@55cf7c381ec0
a: Point@55cf7c381ec0;
b: Point@55cf7c381ec8.
 |_ Rectangle@55cf7c381f60
a: Point@55cf7c381f60;
b: Point@55cf7c381f68.
 |_ Rectangle@55cf7c381fe0
a: Point@55cf7c381fe0;
b: Point@55cf7c381fe8.
 |_ Rectangle@55cf7c382060
a: Point@55cf7c382060;
b: Point@55cf7c382068.
 |_ Rectangle@55cf7c382100
a: Point@55cf7c382100;
b: Point@55cf7c382108.
 |_ Rectangle@55cf7c3826a0
a: Point@55cf7c3826a0;
b: Point@55cf7c3826a8.
 |_ Rectangle@55cf7c382720
a: Point@55cf7c382720;
b: Point@55cf7c382728.
 |_ Rectangle@55cf7c3822d0
a: Point@55cf7c3822d0;
b: Point@55cf7c3822d8.
 |_ Rectangle@55cf7c382350
a: Point@55cf7c382350;
b: Point@55cf7c382358.
 |_ Rectangle@55cf7c3823d0
a: Point@55cf7c3823d0;
b: Point@55cf7c3823d8.
 |_ Rectangle@55cf7c382470
a: Point@55cf7c382470;
b: Point@55cf7c382478.
 |_ Rectangle@55cf7c3824f0
a: Point@55cf7c3824f0;
b: Point@55cf7c3824f8.
 |_ Rectangle@55cf7c382570
a: Point@55cf7c382570;
b: Point@55cf7c382578.
 |_ Rectangle@55cf7c382610
a: Point@55cf7c382610;
b: Point@55cf7c382618.
 |_ Rectangle@55cf7c382bb0
a: Point@55cf7c382bb0;
b: Point@55cf7c382bb8.
 |_ Rectangle@55cf7c382c30
a: Point@55cf7c382c30;
b: Point@55cf7c382c38.
 |_ Point@55cf7c3afbc0
x: '2';
y: '19'.
 |_ Point@55cf7c3afb80
x: '-1';
y: '7'.
 |_ Point@55cf7c3afb20
x: '-9';
y: '15'.
 |_ Point@55cf7c383590
x: '14';
y: '22'.
 |_ Point@55cf7c383610
x: '10';
y: '-10'.
 |_ Point@55cf7c36aeb0
x: '2';
y: '9'.
 |_ Point@55cf7c36af30
x: '24';
y: '12'.
 |_ Point@55cf7c36afb0
x: '-2';
y: '-3'.
 |_ Point@55cf7c3a8710
x: '-5';
y: '7'.
 |_ Point@55cf7c3a8790
x: '-1';
y: '2'.
 |_ Point@55cf7c3a8810
x: '-15';
y: '-20'.
 |_ Point@55cf7c3a8890
x: '-24';
y: '6'.
 |_ Point@55cf7c3a6520
x: '-8';
y: '23'.
 |_ Point@55cf7c3a6528
x: '-7';
y: '13'.
 |_ Point@55cf7c3a6530
x: '14';
y: '-9'.
 |_ Point@55cf7c3a6538
x: '-12';
y: '0'.
 |_ Point@55cf7c3a6540
x: '6';
y: '11'.
 |_ Point@55cf7c3a6548
x: '-21';
y: '-8'.
 |_ Point@55cf7c3a6550
x: '-25';
y: '-22'.
 |_ Point@55cf7c3a6558
x: '-21';
y: '-22'.
 |_ Point@55cf7c3a6560
x: '1';
y: '3'.
 |_ Point@55cf7c3a6568
x: '-23';
y: '21'.
 |_ Point@55cf7c3a6570
x: '-15';
y: '10'.
 |_ Point@55cf7c3a6578
x: '-3';
y: '13'.
 |_ Point@55cf7c3a6580
x: '9';
y: '9'.
 |_ Point@55cf7c3a6588
x: '20';
y: '3'.
 |_ Point@55cf7c3a6590
x: '10';
y: '3'.
 |_ Point@55cf7c3a6598
x: '-19';
y: '-21'.
 |_ Point@55cf7c3a65a0
x: '1';
y: '-1'.
 |_ Point@55cf7c3a65a8
x: '17';
y: '-9'.
 |_ Point@55cf7c3a65b0
x: '17';
y: '-18'.
 |_ Point@55cf7c3a65b8
x: '18';
y: '0'.
 |_ Point@55cf7c3a65c0
x: '19';
y: '24'.
 |_ Point@55cf7c3a65c8
x: '17';
y: '21'.
 |_ Point@55cf7c3a65d0
x: '-23';
y: '22'.
 |_ Point@55cf7c3a65d8
x: '-25';
y: '5'.
 |_ Point@55cf7c3a65e0
x: '2';
y: '-23'.
 |_ Point@55cf7c3a65e8
x: '3';
y: '13'.
 |_ Point@55cf7c3a65f0
x: '12';
y: '-24'.
 |_ Point@55cf7c3a65f8
x: '3';
y: '-2'.
 |_ Point@55cf7c3a6600
x: '10';
y: '-2'.
 |_ Point@55cf7c3a6608
x: '-24';
y: '-2'.
 |_ Point@55cf7c3a6610
x: '-22';
y: '-16'.
 |_ Point@55cf7c3a6618
x: '4';
y: '5'.
 |_ Point@55cf7c3a6620
x: '11';
y: '-3'.
 |_ Point@55cf7c3a6628
x: '23';
y: '3'.
 |_ Point@55cf7c3a6630
x: '4';
y: '18'.
 |_ Point@55cf7c3a6638
x: '-21';
y: '0'.
 |_ Point@55cf7c3a6640
x: '17';
y: '23'.
 |_ Point@55cf7c3a6648
x: '-3';
y: '21'.
 |_ Point@55cf7c3a6650
x: '20';
y: '-1'.
 |_ Point@55cf7c3a6658
x: '1';
y: '-2'.
 |_ Point@55cf7c3a6660
x: '3';
y: '-21'.
 |_ Point@55cf7c3a6668
x: '-12';
y: '-8'.
 |_ Point@55cf7c3a6670
x: '-18';
y: '16'.
 |_ Point@55cf7c3a6678
x: '15';
y: '20'.
 |_ Point@55cf7c3a6680
x: '-9';
y: '17'.
 |_ Point@55cf7c3a6688
x: '-5';
y: '-6'.
 |_ Point@55cf7c3a6690
x: '-22';
y: '24'.
 |_ Point@55cf7c3a6698
x: '-24';
y: '14'.
 |_ Point@55cf7c3a66a0
x: '-4';
y: '24'.
 |_ Point@55cf7c3a66a8
x: '-5';
y: '-22'.
 |_ Point@55cf7c3a66b0
x: '19';
y: '1'.
 |_ Point@55cf7c3a66b8
x: '3';
y: '11'.
 |_ Point@55cf7c3a66c0
x: '-1';
y: '-23'.
 |_ Point@55cf7c3a66c8
x: '7';
y: '-3'.
 |_ Point@55cf7c3a66d0
x: '1';
y: '-15'.
 |_ Point@55cf7c3a66d8
x: '22';
y: '-21'.
 |_ Point@55cf7c3a66e0
x: '-10';
y: '-15'.
 |_ Point@55cf7c3a66e8
x: '-4';
y: '-1'.
 |_ Point@55cf7c3a66f0
x: '-24';
y: '-13'.
 |_ Point@55cf7c3a66f8
x: '-6';
y: '-6'.
 |_ Point@55cf7c3a6700
x: '-19';
y: '14'.
 |_ Point@55cf7c3a6708
x: '13';
y: '-16'.
 |_ Point@55cf7c3a6710
x: '16';
y: '15'.
 |_ Point@55cf7c3a6718
x: '-24';
y: '-13'.
 |_ Point@55cf7c3a6720
x: '16';
y: '-2'.
 |_ Point@55cf7c3a6728
x: '-8';
y: '11'.
 |_ Point@55cf7c3a6730
x: '24';
y: '23'.
 |_ Point@55cf7c3a6738
x: '-3';
y: '0'.
 |_ Point@55cf7c3a6740
x: '-25';
y: '-18'.
 |_ Point@55cf7c3a6748
x: '22';
y: '2'.
 |_ Point@55cf7c3a6750
x: '-8';
y: '21'.
 |_ Point@55cf7c3a6758
x: '6';
y: '9'.
 |_ Point@55cf7c3a6760
x: '-19';
y: '-22'.
 |_ Point@55cf7c3a6768
x: '-14';
y: '-16'.
 |_ Point@55cf7c3a6770
x: '-8';
y: '5'.
 |_ Point@55cf7c3a9700
x: '-3';
y: '-6'.
 |_ Point@55cf7c3a9708
x: '0';
y: '0'.
 |_ Point@55cf7c3a9780
x: '-16';
y: '12'.
 |_ Point@55cf7c3a9788
x: '0';
y: '0'.
 |_ Point@55cf7c3a9800
x: '-15';
y: '22'.
 |_ Point@55cf7c3a9808
x: '0';
y: '0'.
 |_ Point@55cf7c3a98a0
x: '20';
y: '-12'.
 |_ Point@55cf7c3a98a8
x: '0';
y: '0'.
 |_ Point@55cf7c3a9920
x: '-5';
y: '11'.
 |_ Point@55cf7c3a9928
x: '0';
y: '0'.
 |_ Point@55cf7c3a99a0
x: '8';
y: '-19'.
 |_ Point@55cf7c3a99a8
x: '0';
y: '0'.
 |_ Point@55cf7c381c00
x: '-14';
y: '12'.
 |_ Point@55cf7c381c08
x: '0';
y: '0'.
 |_ Point@55cf7c381c80
x: '-6';
y: '6'.
 |_ Point@55cf7c381c88
x: '0';
y: '0'.
 |_ Point@55cf7c381d00
x: '-25';
y: '12'.
 |_ Point@55cf7c381d08
x: '0';
y: '0'.
 |_ Point@55cf7c3a8b70
x: '0';
y: '11'.
 |_ Point@55cf7c3a8b78
x: '0';
y: '0'.
 |_ Point@55cf7c3a8bf0
x: '8';
y: '-23'.
 |_ Point@55cf7c3a8bf8
x: '0';
y: '0'.
 |_ Point@55cf7c3a8c70
x: '-10';
y: '13'.
 |_ Point@55cf7c3a8c78
x: '0';
y: '0'.
 |_ Point@55cf7c3a8d10
x: '1';
y: '23'.
 |_ Point@55cf7c3a8d18
x: '0';
y: '0'.
 |_ Point@55cf7c3a8d90
x: '-21';
y: '-22'.
 |_ Point@55cf7c3a8d98
x: '0';
y: '0'.
 |_ Point@55cf7c3a8e10
x: '15';
y: '-19'.
 |_ Point@55cf7c3a8e18
x: '0';
y: '0'.
 |_ Point@55cf7c3a8eb0
x: '12';
y: '23'.
 |_ Point@55cf7c3a8eb8
x: '0';
y: '0'.
 |_ Point@55cf7c382190
x: '10';
y: '-14'.
 |_ Point@55cf7c382198
x: '0';
y: '0'.
 |_ Point@55cf7c382210
x: '22';
y: '-8'.
 |_ Point@55cf7c382218
x: '0';
y: '0'.
 |_ Point@55cf7c381dc0
x: '-5';
y: '24'.
 |_ Point@55cf7c381dc8
x: '0';
y: '0'.
 |_ Point@55cf7c381e40
x: '12';
y: '9'.
 |_ Point@55cf7c381e48
x: '0';
y: '0'.
 |_ Point@55cf7c381ec0
x: '7';
y: '-23'.
 |_ Point@55cf7c381ec8
x: '0';
y: '0'.
 |_ Point@55cf7c381f60
x: '-18';
y: '5'.
 |_ Point@55cf7c381f68
x: '0';
y: '0'.
 |_ Point@55cf7c381fe0
x: '11';
y: '-25'.
 |_ Point@55cf7c381fe8
x: '0';
y: '0'.
 |_ Point@55cf7c382060
x: '23';
y: '-10'.
 |_ Point@55cf7c382068
x: '0';
y: '0'.
 |_ Point@55cf7c382100
x: '2';
y: '-4'.
 |_ Point@55cf7c382108
x: '0';
y: '0'.
 |_ Point@55cf7c3826a0
x: '13';
y: '23'.
 |_ Point@55cf7c3826a8
x: '0';
y: '0'.
 |_ Point@55cf7c382720
x: '24';
y: '-10'.
 |_ Point@55cf7c382728
x: '0';
y: '0'.
 |_ Point@55cf7c3822d0
x: '24';
y: '-2'.
 |_ Point@55cf7c3822d8
x: '0';
y: '0'.
 |_ Point@55cf7c382350
x: '2';
y: '3'.
 |_ Point@55cf7c382358
x: '0';
y: '0'.
 |_ Point@55cf7c3823d0
x: '-17';
y: '3'.
 |_ Point@55cf7c3823d8
x: '0';
y: '0'.
 |_ Point@55cf7c382470
x: '5';
y: '22'.
 |_ Point@55cf7c382478
x: '0';
y: '0'.
 |_ Point@55cf7c3824f0
x: '-12';
y: '14'.
 |_ Point@55cf7c3824f8
x: '0';
y: '0'.
 |_ Point@55cf7c382570
x: '-13';
y: '-11'.
 |_ Point@55cf7c382578
x: '0';
y: '0'.
 |_ Point@55cf7c382610
x: '-11';
y: '-4'.
 |_ Point@55cf7c382618
x: '0';
y: '0'.
 |_ Point@55cf7c382bb0
x: '12';
y: '-14'.
 |_ Point@55cf7c382bb8
x: '0';
y: '0'.
 |_ Point@55cf7c382c30
x: '11';
y: '-21'.
 |_ Point@55cf7c382c38
x: '0';
y: '0'.
```
