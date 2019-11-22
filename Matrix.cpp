#include "Matrix.h"
/*MATRIX SOLVE*/

int GetMatrix(string name){
	if(name == "A" || name == "a") return 1;
	else if(name == "B" || name == "b") return 2;
	else if(name == "C" || name == "c") return 3;
	else if(name == "Ans" || name == "ans") return 4;
	return 0;
}

void InputMatrix(Matrix &input)
{
	for(int i = 2; i < 49; i++){
		for(int j = 6; j < 29; j++){
			DrawCharacter(i, j, white, blank);
		}
	}
	
	DrawString(2, 6, white, "Nhap so dong: ");	
	
	GotoXY(16, 6);
	cin >> input.row;
	cin.ignore(); 
	
	DrawString(2, 7, white, "Nhap so cot: "); 
	GotoXY(15, 7);
	cin >> input.column;
	cin.ignore(); 
	
	DrawString(2, 8, white, "Nhap ma tran: ");
	input.mtx = new float*[input.row];
	for (int i = 0; i < input.row; i++) {
		input.mtx[i] = new float[input.column];
		for (int j = 0; j < input.column; j++) {
			GotoXY(j*5 + 2, i*2 + 10);
			cin >> input.mtx[i][j]; 	
		}
	}
	getch();
	fflush(stdin);
	GetAsyncKeyState(VK_RETURN);
}
void OutputMatrix(Matrix input)
{
	for(int i = 2; i < 49; i++){
		for(int j = 6; j < 29; j++){
			DrawCharacter(i, j, white, blank);
		}
	}
	
	if(input.column <= 0 || input.row <= 0) DrawString(2, 6, white, "Null Matrix"); 
	else{
		for (int i = 0; i < input.row; i++) {
			for (int j = 0; j < input.column; j++) {
				GotoXY(j*5 + 2, i*2 + 6);
				cout << input.mtx[i][j];
			}
		}
	}
	
	getch();
	fflush(stdin);
	GetAsyncKeyState(VK_RETURN);
}

void DeleteMatrix(Matrix input){
	for (int i = 0; i < input.row; i++){
		delete[] input.mtx[i];
	}
	delete input.mtx;
}

Matrix SaveData(Matrix in)//Gui du lieu vao ma tran tam
{
	Matrix temp;
	temp.column = in.column;
	temp.row = in.row;
	temp.mtx = new float* [in.row];
	for (int i = 0; i < in.row; i++){
		temp.mtx[i] = new float[in.column];
		for (int j = 0; j < in.column; j++){
			temp.mtx[i][j] = in.mtx[i][j];
		}
	}
	return temp;
}
//Nhan ma tran

Matrix MultiplyMatrix(Matrix in1, Matrix in2){
	//Tao ma tran tich
	Matrix multi;
	multi.column = in2.column;
	multi.row = in1.row;
	int a = 0;
	if (in1.column != in2.row) {//Dieu kien khong the nhan tra ve -1 de kiem tra trong main
		multi.column = -1;
		return multi; 
	}
	multi.mtx = new float* [multi.row];
	for (int i = 0; i < multi.row; i++) {
		multi.mtx[i] = new float[multi.column];
		while (a < multi.column) {
			multi.mtx[i][a] = 0;
			for (int j = 0; j < in1.column; j++) {
				multi.mtx[i][a] += in1.mtx[i][j] * in2.mtx[j][a];
				/*Nhân ma tran theo cong thuc  c(0,0) = a(0,0)*b(0,0) + ....+ a(0,n)*b(n,0)*/

			}
			a++;
		}
		a = 0;
	}
	return multi;
}

//Tim dinh thuc
float CalcDeterminant(Matrix in)
{
	//Tinh dinh thuc bang thuat toan Bareiss
	float result = 1;
	if (in.column != in.row) return -9999999;//Dieu kien khong the tinh dinh thuc tra ve -1 de kiem tra trong main
	int n = in.column;
	bool a = 0, b = a;
	float sign = 1;
	Matrix temp1 = SaveData(in);
	BareissMatrix(temp1, sign);
	/*Vong for de kiem tra neu ma tran sau khi bareiss co 1 dong hoac 1 cot bang 0 thi tra ve det = 0*/
	for (int i = 0; i < n; i++){
		for (int j = 0; j < n; j++){
			a += temp1.mtx[i][j];//Cong dong kiem tra
			b += temp1.mtx[j][i];//Cong cot kiem tra
		}
		if (a == 0 || b == 0){//Chi can 1 dong hoac 1 cot bang 0 thi tra ve 0
			return 0;
		}
		a = 0;
		b = 0;
	}
	//sign la dau cua cua det vi trong thuat toan bareiss em co doi 2 dong voi nhau & doi thi phai doi dau
	return sign * temp1.mtx[n / 2][n / 2]; //Em co neu y tuong chinh duoi phan code bareiss vi sao phai tra ve vi tri chinh giua
}

//Nghich dao ma tran
Matrix InverseMatrix(Matrix in){
	Matrix out;
	out.column = in.column;
	out.row = in.row;
	//Tim ma tran phu hop cua ma tran input sau do nhan ca ma tran phu hop do voi 1/det(input)
	if (out.column != out.row) // Neu khong vuong tra ve -1
	{
		out.column = -1;
		return out;
	}
	else {
		//Tao ma tran chua ma tran nghich dao
		int n = in.column;
		out.column = n;
		out.row = n;
		out.mtx = new float* [n];
		
		if (CalcDeterminant(in) == 0) {
			
			out.column = 0;
		}
		else {
			for (int i = 0; i < n; i++) {
				out.mtx[i] = new float[n];
				for (int j = 0; j < n; j++) {
					Matrix temp = AlgebraicComplement(in, i, j);
					out.mtx[i][j] = pow(-1.0, float(i + j)) * CalcDeterminant(temp);
					//phan tu cua ma tran phù hop = -1^(i+j)*det(c(i,j))
				}
			}
			//Chuyen vi de hoan thanh viec tim ma tran phu hop
			Transposition(out);
			float power = 1.0 / CalcDeterminant(in);//Tìm 1/det(input) và nhan voi ma tran phu hop
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < n; j++) {
					out.mtx[i][j] *= power;
				}
			}
		}
		return out;
	}
}
Matrix AlgebraicComplement(Matrix in, int r, int c)//Tim ma tran xoa di dong i cot j ( int r la dong i ,int c la cot j)
{
	int n = in.column - 1;
	Matrix out;
	out.column = n;
	out.row = n;
	int k, l = k = 0;
	out.mtx = new float* [n];//Cap phat
	for (int i = 0; i < n; i++){
		out.mtx[i] = new float[n];
	}
	for (int i = 0; i < in.column; i++) {//Lay phan tu khong thuoc dong i cot j dua vao ma tran out
		for (int j = 0; j < in.column; j++){
			if (i != r && j != c){
				out.mtx[k][l] = in.mtx[i][j];
				if (l == n - 1){
					l = 0;
					k++;
				}
				else l++;
			}
		}
	}
	return out;
}
void Transposition(Matrix in)//Chuyen vi ma tran
{
	/*
		a b c		a d g
		d e f	->	b e f
		g h j		c f j
	*/
	int n = in.column;
	for (int i = 1; i < n; i++){
		for (int j = 0; j < i; j++){
			float temp = in.mtx[i][j];
			in.mtx[i][j] = in.mtx[j][i];
			in.mtx[j][i] = temp;
		}
	}
}
//Tim hang
void BareissMatrix(Matrix in, float& sign)
{
	//Thuat toan bareiss (montante)
	//Ý tuongg chính
	/* a b c				x 0 0
	   c d e		->		0 x 0
	   f g h				0 0 x	*/
	   //x là dinh thuc cua ma tr?n //
	   //Chi tiet thuat em xin trình bày trong báo cáo
	int col = in.column;//Toi gian cách goi bien
	int row = in.row;
	int a, b = a = 0;//Buoc nhay cho Bareiss
	float pivot[100];//Phan tu pivot de chia
	pivot[0] = 1;
	int flag = 0;//Bien kiem tra xem pivot co thay doi khong
	while (a < row){
		if (a + 1 < row){
			if (in.mtx[a][b] == 0 && in.mtx[a + 1][b] != 0){//doi dong neu phan tu duoc chon bang 0 nhung phan tu duoi khac 0
				for (int j = 0; j < col; j++){
					float temp = in.mtx[a][j];
					in.mtx[a][j] = in.mtx[a + 1][j];
					in.mtx[a + 1][j] = temp;
				}
				sign *= -1;
			}
		}
		int point;//Vi tri moi cua de nhan va chia
		Matrix temp = SaveData(in);
		if (a + 1 < col){
			pivot[a + 1] = in.mtx[a][b];
			if (pivot[a + 1] == 0){//Sau khi doi dong neu van con bang 0 thi su dung phan tu ke ben
				for (int i = b ; i < col; i++){
					if (in.mtx[a][i] != 0){
						pivot[a + 1] = in.mtx[a][i];
						flag = 1;
						point = i;//vi tri moi de nhan
						break;
					}
				}
			}
		}
		/*Công thuc tính
			a,b là buoc nhay theo dòng
			pivot thay doi moi lan a b tang
			tai vi trí dong i cot j a[i,j]= (a[a,b]*a[i,j] - a[i][a]*a[a][j])/pivot;
		*/
		for (int i = 0; i < row; i++){
			if (i != a){
				if (flag == 0){
					for (int j = 0; j < col; j++){//Neu khong su dung pivot tai vi tri khac thi tinh binh thuong
						in.mtx[i][j] = (temp.mtx[a][b] * temp.mtx[i][j] - temp.mtx[i][a] * temp.mtx[a][j]) / pivot[a];
					}
				}
				if (flag == 1){
					for (int j = 0; j < col; j++){//Neu su dung pivot thay doi thi su dung vi tri point da gan o tren
						in.mtx[i][j] = (temp.mtx[a][point] * temp.mtx[i][j] - temp.mtx[i][point] * temp.mtx[a][j]) / pivot[a];
					}
				}
			}
		}
		flag = 0;
		//Kiem tra luc bien doi neu co 1 dong  bang 0 ma ben duoi van con dong khac 0 thi doi dong
		if (a + 2 < row) {
			bool zero = 1;
			bool unzero = 1;
			for (int k = 0; k < col; k++) {
				if (in.mtx[a + 1][k] == 0){
					zero = 0;
				}
				else {
					zero = 1;
					break;
				}
				if (in.mtx[a + 2][k] != 0){
					unzero = 0;
				}
			}
			if (zero == 0 && unzero != 0) break;
			if (zero == 0 && unzero == 0){
				for (int j = 0; j < col; j++){
					float temp = in.mtx[a + 1][j];
					in.mtx[a + 1][j] = in.mtx[a + 2][j];
					in.mtx[a + 2][j] = temp;
				}
				sign *= -1;
			}
		}
		//Kiem tra lai sau khi buoc nhay tang
		if (row != 1 && a + 1 < row)
		{
			bool zero1 = 1;
			for (int k = 0; k < col; k++) {
				if (in.mtx[a + 1][k] == 0){
					zero1 = 0;
				}
				else {
					zero1 = 1;
					break;
				}
			}
			if (zero1 == 0) break;
		}
		a++;
		b++;
	}
}
int Ranking(Matrix in)
{
	//Tim hang ma tran
	//em da noi so thuat toan bareiss o phia tren sau khi bien doi chi can kiem tra xem bao nhieu dong = 0
	Matrix temp = SaveData(in);
	float sign = 1;
	BareissMatrix(temp, sign);
	int rank = 0;
	bool zero = 1;
	for (int i = 0; i < in.row; i++){
		for (int j = 0; j < in.column; j++){
			if (temp.mtx[i][j] == 0){
				zero = 0;
			}
			else{
				zero = 1;
				break;
			}
		}
		if (zero == 1){
			rank++;
		}
		zero = 1;
	}
	return rank;
}
//Giai he phuong trinh tuyen tinh
void SolveSystem(Matrix in){
	//Giai phuong trinh bang cach dieu kien hang ma tran
	//Tach ma tran input thanh ma tran A va B (A*X=B) => X= A^(-1)*B
	
	Matrix result;
	int row = in.row;//Toi gian cach goi bien
	int col = in.column;
	Matrix A;/*Tach ma tran A*/
	A.column = col - 1;
	A.row = row;
	A.mtx = new float* [row];//Cap phat ma tran
	for (int i = 0; i < row; i++) {
		A.mtx[i] = new float[A.column];
		for (int j = 0; j < A.column; j++) {
			A.mtx[i][j]	= in.mtx[i][j];
		}
	}
	Matrix B;/*Tach ma tran B*/
	B.column = 1;
	B.row = row;
	B.mtx = new float* [row];//Cap phat ma tran
	for (int i = 0; i < row; i++) {
		B.mtx[i] = new float[1];
		B.mtx[i][0] = in.mtx[i][col - 1];
	}
	int rankA = Ranking(A);
	int rankAB = Ranking(in);
	//Hang cua ma tran A < hang ma tran input thi vo nghiem
	if (rankA < rankAB){
		DrawString(2, 8, white, "He phuong trinh vo nghiem !!!");
	}
	//Hang cua ma tran A = hang ma tran input thi co nghienm
	//Neu hang A bang luon so cot cua A thi nghhiem duy nhat
	//Neu hang A bang luon so cot cua A thi vo so nghiem
	if (rankA == rankAB && rankA == A.column){
		if (col - 1 == row){
			DrawString(2, 8, white, "He phuong trinh co nghiem duy nhat !!!");
			Matrix _A = InverseMatrix(A);
			result = MultiplyMatrix(_A, B);
			OutputSystem(result);
		}
		else{//Day la truong hop dac biet
		/* 1 1 2		Neu xet binh thuong thi day co vo so nghiem nhung phai xet ky la chi can 2 phuong vi phuong trinh thu 3 bi thua
		   1 -1 0		Dua 2 phuong trinh trong 3 phuong trinh vao ma tran moi roi de qui giai ma tran moi do
		   1 -3 -2
		*/
			Matrix temp;
			temp.column = col;
			temp.row = row - 1;
			temp.mtx = new float* [temp.row];
			for (int i = 0; i < temp.row; i++) {
				temp.mtx[i] = new float[temp.column];
				for (int j = 0; j < temp.column; j++) {
					temp.mtx[i][j] = in.mtx[i][j];
				}
			}
			SolveSystem(temp);
		}
	}
	if (rankA == rankAB && rankA < A.column){
		DrawString(2, 8, white, "He phuong trinh vo so nghiem !!!");
		DrawString(2, 9, white, "Nghhiem tong quat la: ");
		int count = A.column - rankA;
		OutputGenerality(in, count);

	}
	DeleteMatrix(A);
	DeleteMatrix(B);
}

void OutputSystem(Matrix in)//Xuat nghiem cua ma tran theo dang x1=... , x2=.....
{
	DrawString(2, 6, white, "Nghiem cua he: ");
	for (int i = 0; i < in.row; i++){	
		GotoXY(2, i + 9);
		cout << "x" << i + 1 << " = " << in.mtx[i][0];
	}
}

void OutputGenerality(Matrix in,int count)//Xuat nghiem tong quat cua hpt(neu he vo so nghiem)
{
	char unknow[10] = { 'a','b','c','d','e','f','g','h','i','j' };
	float arr[10];
	int dem = 0;
	int t = 0;
	int row = in.row;//Toi gian cach goi bien
	int col = in.column;
	Matrix temp = SaveData(in);
	float sign = 1;
	BareissMatrix(temp, sign);
	//Xuat nhung bien theo bien tu do
	//Em vua tinh toan vua xuat
	for (int i = 0; i < col - 1 - count; i++) {
		for (int j = col - 1; j > i; j--) {
			if (j == col - 1) {
				arr[dem] = temp.mtx[i][j] / temp.mtx[i][i];
			}
			else {
				arr[dem] = -temp.mtx[i][j] / temp.mtx[i][i];
			}
			dem++;
		}
		GotoXY(2, i + 10);
		cout << "x" << i + 1 << " = ";
		int t = 0;
		for (int k = 0; k < col - 1; k++) {
			if (k == 0) {
				if (arr[k] != 0) {
					cout << arr[k] << " ";
				}
			}
			else {
			//Sau day la xet dau neu am thi xuat binh thuong neu duong thi them +
				if (arr[k] != 0) {
					if (arr[k] < 0) {
						cout << arr[k] << unknow[t] << " ";
						t++;
					}
					else {
						cout << "+ " << arr[k] << unknow[t] << " ";
						t++;
					}
				}
			}
		}
		dem = 0;
	}

	//Xuat nhung nghiem la bien  tu do
	for (int i = col - 1 - count, k = 0; i < col - 1; i++, k++){
		GotoXY(2, i + 10);
		cout << "x" << i + 1 << " = " << unknow[k] << endl;
	}
}


