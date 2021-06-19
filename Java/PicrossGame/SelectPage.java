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
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;

public class SelectPage extends JFrame implements ActionListener, MouseListener{
	private JFrame jf;
	private JButton start;
	private JButton howto;
	private JLabel s;
	private JLabel first5,second5,third5,first10,second10,third10,first15,second15,third15;
	private JPanel choosePanel;
	public SelectPage() {
		
		setTitle("Picross");
		setSize(500,600);
		setLocationRelativeTo(null); //좌표지정해주는거도잇음
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);// 종료를 위해 쓰는것

		Container c= getContentPane();
		c.setLayout(null);

		s =new JLabel("~Choose Stage~");
		s.setFont(new Font("Comic Sans MS",Font.BOLD,30));
		s.setBounds(130, 60, 270, 50);

		URL url1 = SelectPage.class.getResource("img/5by5.png");
		URL url2 = SelectPage.class.getResource("img/10by10.png");
			
		ImageIcon first5img = new ImageIcon(url1);
		Image image=first5img.getImage();
		Image newimg = image.getScaledInstance(85, 85, Image.SCALE_SMOOTH);
		first5img= new ImageIcon(newimg);

		ImageIcon first10img = new ImageIcon(url2);
		Image image2= first10img.getImage();
		Image newimg2 = image2.getScaledInstance(85, 85, Image.SCALE_SMOOTH);
		first10img= new ImageIcon(newimg2);


		first5=new JLabel(first5img);
		first5.addMouseListener(this);
		first10=new JLabel(first10img);
		first10.addMouseListener(this);

		choosePanel = new JPanel();
		choosePanel.setLayout(new GridLayout(2,1,3,3));
		choosePanel.add(first5);
		choosePanel.add(first10);
		choosePanel.setBounds(100,120,300,300);

		c.add(s);
		c.add(choosePanel);
		setVisible(true);
	}

	public static void main(String[] args) {

	}

	@Override
	public void mouseClicked(MouseEvent e) {
		// TODO Auto-generated method stub
		Object obj = e.getSource();
		if(obj==first5) {
			//first5불러온 게임페이지
			new GamePage();
			this.setVisible(false);
		}
		if(obj==first10) {
			new GamePage2();
			this.setVisible(false);
		}
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
	public void actionPerformed(ActionEvent arg0) {
		// TODO Auto-generated method stub
		
	}

}
