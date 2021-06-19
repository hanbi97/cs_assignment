import java.awt.Container;
import java.sql.*;
import java.awt.Font;
import java.awt.GridLayout;
import java.awt.Image;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.net.URL;

import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JComboBox;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JList;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTextField;

public class Name extends JFrame implements ActionListener, MouseListener{
	private JFrame jf;
	private JButton ok;
	private JLabel s;
	private JLabel  newname,isName;
	private JComboBox<String> choosename;
	private JTextField inputname;
	private JPanel choosePanel;
	String[] names= {"choosename"
	};
	String inputn;
	String myname;
	public Name() {

		setTitle("Picross");
		setSize(500,600);
		setLocationRelativeTo(null); //좌표지정해주는거도잇음
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);// 종료를 위해 쓰는것

		Container c= getContentPane();
		c.setLayout(null);

		s =new JLabel("~Write Information~");
		s.setFont(new Font("Comic Sans MS",Font.BOLD,27));
		s.setBounds(110, 60, 290, 50);

		isName = new JLabel("Is your name on there?");
		isName.setFont(new Font("Comic Sans MS",Font.BOLD,20));
		isName.setBounds(80,40,450,30);
		choosename = new JComboBox<String>(names);
		choosename.setBounds(80,80,200,30);

		newname = new JLabel("Write new username");
		newname.setFont(new Font("Comic Sans MS",Font.BOLD,20));
		newname.setBounds(80,150,500,30);
		inputname = new JTextField();
		inputname.addActionListener(this);
		inputname.setBounds(80,200,200,30);
		ok = new JButton("OK");
		//ok.setFont(new Font("Comic Sans MS",Font.BOLD,20));
		ok.setBounds(300,200,50,30);
		ok.addActionListener(this);
		myname=inputname.getText();

		choosePanel = new JPanel();
		choosePanel.setLayout(null);
		choosePanel.add(isName);
		choosePanel.add(choosename);
		choosePanel.add(newname);
		choosePanel.add(inputname);
		choosePanel.add(ok);
		choosePanel.setBounds(0,100,400,500);

		c.add(s);
		c.add(choosePanel);
		setVisible(true);

		
	}

	public static void main(String[] args) {
		Name n = new Name();
	//	String ss = n.inputname.getText();
		

	}

	@Override
	public void mouseClicked(MouseEvent e) {
		// TODO Auto-generated method stub
		

	}

	@Override
	public void mouseEntered(MouseEvent arg0) {
		// TODO Auto-generated method stub

	}

	@Override
	public void mouseExited(MouseEvent arg0) {
		// TODO Auto-generated method stub

	}

	@Override
	public void mousePressed(MouseEvent arg0) {
		// TODO Auto-generated method stub

	}

	@Override
	public void mouseReleased(MouseEvent arg0) {
		// TODO Auto-generated method stub

	}

	@Override
	public void actionPerformed(ActionEvent e) {
		// TODO Auto-generated method stub
		Object obj = e.getSource();
		if(obj==ok) {
			//first5불러온 게임페이지
			
			Statement stmt= null;
			try {
				Connection conn = DriverManager.getConnection("jdbc:oracle:thin:@127.0.0.1:1521:XE", "temp","0000");
				stmt=conn.createStatement();
				String sql ="insert into tb "+
							"values('"+myname+"',0)";
				stmt.executeUpdate(sql);
			System.out.println("insert records");
			}
			catch (SQLException e1) {
				e1.printStackTrace();
			}

			new SelectPage();
			this.setVisible(false);
		}
	}

}
