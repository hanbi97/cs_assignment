import java.util.Scanner;

public class GuGuDan {

	public static void main(String[] args) {
		int[][]a = new int [8][9];
		Scanner sc=new Scanner(System.in);
		System.out.print("���۴� �Է�: ");
		int n= sc.nextInt();
		System.out.print("���� �Է�: ");
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
			//1~9���� ���尪���
			for (int i = (n-2); i <= (m-2); i++) {
				//��´ܹ����Է�
				System.out.print((i+2)+"*"+(j)+"="+a[i][j-1]+"\t");
			}
			System.out.println();
		}
		//		

	}

}
