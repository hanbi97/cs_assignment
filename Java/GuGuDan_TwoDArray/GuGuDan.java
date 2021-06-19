import java.util.Scanner;

public class GuGuDan {

	public static void main(String[] args) {
		int[][]a = new int [8][9];
		Scanner sc=new Scanner(System.in);
		System.out.print("시작단 입력: ");
		int n= sc.nextInt();
		System.out.print("끝단 입력: ");
		int m= sc.nextInt();

		for(int i=0; i<8; i++)
		{

			for(int j=1;j<10;j++)
			{
				a[i][j-1]=(i+2)*j;
				//System.out.print(j+1)+ "*" + (i+1)+ "=" + a[i][j-1]+"\t");
			}
			//System.out.println();
		}
		//
		for (int j = 1; j<10; j++) {
			//1~9곱한 저장값출력
			for (int i = (n-2); i <= (m-2); i++) {
				//출력단범위입력
				System.out.print((i+2)+"*"+(j)+"="+a[i][j-1]+"\t");
			}
			System.out.println();
		}
		//		

	}

}
