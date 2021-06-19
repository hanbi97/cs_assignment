//���ǵ� �����Ŵ�

import javax.swing.*;

import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.File;
import java.io.FileInputStream;
import java.io.InputStream;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;
import java.io.*;


public class MainPage extends JFrame implements ActionListener {
	private JButton start;
	private JButton howto;
	private JLabel s;
	
	public MainPage(String title) {

		setTitle("Picross");
		setSize(500,600);
		setLocationRelativeTo(null); //��ǥ�������ִ°ŵ�����
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);// ���Ḧ ���� ���°�

		Container c= getContentPane();
		c.setLayout(null);

		s =new JLabel("<html>��Picross��</html>");
		s.setFont(new Font("Comic Sans MS",Font.BOLD,45));
		s.setBounds(130, 180, 240, 50);

		start = new JButton("START");
		start.setFont(new Font("Comic Sans MS",Font.BOLD,15));
		start.setBounds(110, 300, 100, 30);//��ġ��ǥ x,y ������Ʈũ�� ����,����
		start.addActionListener(this);

		howto = new JButton("HOWTO");
		howto.setFont(new Font("Comic Sans MS",Font.BOLD,15));
		howto.setBounds(280,300,100,30);
		howto.addActionListener(this);

		c.add(s);
		c.add(start);
		c.add(howto);


		setVisible(true);
	}
	
	public static void main(String[] args) {
		
		try {
			Class.forName("oracle.jdbc.driver.OracleDriver");
			Connection conn = DriverManager.getConnection("jdbc:oracle:thin:@127.0.0.1:1521:XE", "temp","0000");
			System.out.println("db����Ϸ�");
		} catch (ClassNotFoundException e) {
			e.printStackTrace();
		}
		catch (SQLException e) {
			e.printStackTrace();
		}


		try {
			UIManager.setLookAndFeel("javax.swing.plaf.nimbus.NimbusLookAndFeel");
		} catch (Exception e) {
			e.printStackTrace();
		}

		new MainPage("Picross");
	}

	@Override
	public void actionPerformed(ActionEvent e) {
		Object obj =e.getSource();
		if(obj==start) {
			new Name();
			this.setVisible(false);
		}
		if(obj==howto) {
			new Howto();
			this.setVisible(false);
		}
	}

}


