import java.awt.Color;
import java.awt.Container;
import java.awt.Font;
import java.awt.GridLayout;
import java.awt.Image;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.net.URL;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.Statement;

import javax.swing.AbstractButton;
import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JMenu;
import javax.swing.JMenuBar;
import javax.swing.JMenuItem;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.SwingConstants;



public class GamePage extends JFrame implements ActionListener, MouseListener{
	private JFrame jf;
	private JMenuBar mb;
	private JMenu m;
	private Container c;
	private JMenuItem newgame,save,exit;
	private JLabel b0;
	private JLabel lifelabel;
	private int countlife=3;
	private JPanel main, life, xbutton, playbutton;
	private JLabel[] rowlabel = new JLabel[5];
	private JLabel[][] gridlabel = new JLabel[5][5];
	private int[][] map1= {
			{0,0,0,0,0},
			{-1,0,0,0,-1},
			{-1,-1,0,-1,-1},
			{-1,0,0,0,-1},
			{0,0,0,0,0}
	};

	public GamePage() {
		//jf=selectPage;
		setTitle("Picross");
		setSize(500,600);
		setLocationRelativeTo(null); //좌표지정해주는거도잇음
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);// 종료를 위해 쓰는것

		Container c= getContentPane();
		c.setLayout(null);

		mb = new JMenuBar();
		
		m= new JMenu("Setting");
		m.setFont(new Font("Comic Sans MS",Font.BOLD,14));
		mb.add(m);
		
		newgame = new JMenuItem("NewGame");
		newgame.setFont(new Font("Comic Sans MS",Font.BOLD,14));
		m.add(newgame);
		newgame.addActionListener(this);
	
		m.addSeparator();
		
		save = new JMenuItem("Save");
		save.setFont(new Font("Comic Sans MS",Font.BOLD,14));
		m.add(save);
		m.addSeparator();
		save.addActionListener(this);
		
		exit = new JMenuItem("Exit");
		exit.setFont(new Font("Comic Sans MS",Font.BOLD,14));
		m.add(exit);
		exit.addActionListener(this);

		life = new JPanel();
		life.setBounds(50,440,130,40);
		lifelabel = new JLabel("Lifes: "+Integer.toString(countlife));
		lifelabel.setFont(new Font("Comic Sans MS",Font.BOLD,21));
		life.add(lifelabel);

		main=new JPanel();
		main.setLayout(new GridLayout(6,6,1,1));
		URL url1 = SelectPage.class.getResource("img/back.png");
		ImageIcon backb = new ImageIcon(url1);
		Image image= backb.getImage();
		Image newimg = image.getScaledInstance(20, 20, Image.SCALE_SMOOTH);
		backb= new ImageIcon(newimg);

		main.setBounds(50,40,400,400);
		b0 = new JLabel(backb);
		b0.setSize(40, 100);
		b0.setBackground(new Color(0,51,101));
		b0.setOpaque(true);
		b0.addMouseListener(this);
		main.add(b0);
		
		for(int i=0; i<5;i++) {
			rowlabel[i] = new JLabel("",SwingConstants.CENTER);
			rowlabel[i].setSize(40, 100);
			rowlabel[i].setBackground(new Color(0,51,101));
			rowlabel[i].setForeground(Color.WHITE);
			rowlabel[i].setOpaque(true);
			rowlabel[i].setFont(new Font("Comic Sans MS",Font.BOLD,10));
			main.add(rowlabel[i]);
		}
		rowlabel[0].setText("<html>1<br/>1</html>");
		rowlabel[1].setText("<html>2<br/>2</html>");
		rowlabel[2].setText("5");
		rowlabel[3].setText("<html>2<br/>2</html>");
		rowlabel[4].setText("<html>1<br/>1</html>");

		JLabel b1= new JLabel("5",SwingConstants.CENTER);
		b1.setFont(new Font("Comic Sans MS",Font.BOLD,10));
		b1.setSize(100, 40);
		b1.setBackground(new Color(0,51,101));
		b1.setForeground(Color.WHITE);
		b1.setOpaque(true);
		main.add(b1);

		for (int i = 0; i <5; i++) {
			if(map1[0][i]==0)
			{
				gridlabel[0][i]= new JLabel("0");
				gridlabel[0][i].setSize(40, 40);
				gridlabel[0][i].setBackground(Color.WHITE);
				gridlabel[0][i].setForeground(Color.WHITE);
				gridlabel[0][i].setOpaque(true);
				main.add(gridlabel[0][i]);}
			else if(map1[0][i]==-1) {
				gridlabel[0][i]= new JLabel("-1");
				gridlabel[0][i].setSize(40, 40);
				gridlabel[0][i].setBackground(Color.WHITE);
				gridlabel[0][i].setForeground(Color.WHITE);
				gridlabel[0][i].setOpaque(true);
				main.add(gridlabel[0][i]);
			}
			gridlabel[0][i].addMouseListener(this);

		}
		JLabel b2= new JLabel("3",SwingConstants.CENTER);
		b2.setFont(new Font("Comic Sans MS",Font.BOLD,10));
		b2.setSize(100, 40);
		b2.setBackground(new Color(0,51,101));
		b2.setForeground(Color.WHITE);
		b2.setOpaque(true);
		main.add(b2);

		for (int i = 0; i < 5; i++) {
			if(map1[1][i]==0)
			{
				gridlabel[1][i]= new JLabel("0");
				gridlabel[1][i].setSize(40, 40);
				gridlabel[1][i].setBackground(Color.WHITE);
				gridlabel[1][i].setForeground(Color.WHITE);
				gridlabel[1][i].setOpaque(true);
				main.add(gridlabel[1][i]);
			}
			else if(map1[1][i]==-1) {
				gridlabel[1][i]= new JLabel("-1");
				gridlabel[1][i].setSize(40, 40);
				gridlabel[1][i].setBackground(Color.WHITE);
				gridlabel[1][i].setForeground(Color.WHITE);
				gridlabel[1][i].setOpaque(true);
				main.add(gridlabel[1][i]);
			}
			gridlabel[1][i].addMouseListener(this);
		}
		JLabel b3= new JLabel("1",SwingConstants.CENTER);
		b3.setFont(new Font("Comic Sans MS",Font.BOLD,10));
		b3.setSize(100, 40);
		b3.setBackground(new Color(0,51,101));
		b3.setForeground(Color.WHITE);
		b3.setOpaque(true);
		main.add(b3);
		for (int i = 0; i < 5; i++) {
			if(map1[2][i]==0)
			{
				gridlabel[2][i]= new JLabel("0");
				gridlabel[2][i].setSize(40, 40);
				gridlabel[2][i].setBackground(Color.WHITE);
				gridlabel[2][i].setForeground(Color.WHITE);
				gridlabel[2][i].setOpaque(true);
				main.add(gridlabel[2][i]);
			}
			else if(map1[2][i]==-1) {
				gridlabel[2][i]= new JLabel("-1");
				gridlabel[2][i].setSize(40, 40);
				gridlabel[2][i].setBackground(Color.WHITE);
				gridlabel[2][i].setForeground(Color.WHITE);
				gridlabel[2][i].setOpaque(true);
				main.add(gridlabel[2][i]);
			}
			gridlabel[2][i].addMouseListener(this);
		}

		JLabel b4= new JLabel("3",SwingConstants.CENTER);
		b4.setFont(new Font("Comic Sans MS",Font.BOLD,10));
		b4.setSize(100, 40);
		b4.setBackground(new Color(0,51,101));
		b4.setForeground(Color.WHITE);
		b4.setOpaque(true);
		main.add(b4);

		for (int i = 0; i < 5; i++) {
			if(map1[3][i]==0)
			{
				gridlabel[3][i]= new JLabel("0");
				gridlabel[3][i].setSize(40, 40);
				gridlabel[3][i].setBackground(Color.WHITE);
				gridlabel[3][i].setForeground(Color.WHITE);
				gridlabel[3][i].setOpaque(true);
				main.add(gridlabel[3][i]);
			}
			else if(map1[3][i]==-1) {
				gridlabel[3][i]= new JLabel("-1");
				gridlabel[3][i].setSize(40, 40);
				gridlabel[3][i].setBackground(Color.WHITE);
				gridlabel[3][i].setForeground(Color.WHITE);
				gridlabel[3][i].setOpaque(true);
				main.add(gridlabel[3][i]);
			}
			gridlabel[3][i].addMouseListener(this);
		}
		JLabel b5= new JLabel("5",SwingConstants.CENTER);
		b5.setFont(new Font("Comic Sans MS",Font.BOLD,10));
		b5.setSize(100, 40);
		b5.setBackground(new Color(0,51,101));
		b5.setForeground(Color.WHITE);
		b5.setOpaque(true);
		main.add(b5);
		for (int i = 0; i < 5; i++) {
			if(map1[4][i]==0)
			{
				gridlabel[4][i]= new JLabel("0");
				gridlabel[4][i].setSize(40, 40);
				gridlabel[4][i].setBackground(Color.WHITE);
				gridlabel[4][i].setForeground(Color.WHITE);
				gridlabel[4][i].setOpaque(true);
				main.add(gridlabel[4][i]);
			}
			else if(map1[4][i]==-1) {
				gridlabel[4][i]= new JLabel("-1");
				gridlabel[4][i].setSize(40, 40);
				gridlabel[4][i].setBackground(Color.WHITE);
				gridlabel[4][i].setForeground(Color.WHITE);
				gridlabel[4][i].setOpaque(true);
				main.add(gridlabel[4][i]);
			}
			gridlabel[4][i].addMouseListener(this);
		}

		setJMenuBar(mb);
		c.add(main);
		c.add(life);
		setVisible(true);
	}

	public static void main(String[] args) {
	}

	@Override
	public void actionPerformed(ActionEvent e) {
		Object obj = e.getSource();
		if(obj==newgame) {
			int result = JOptionPane.showConfirmDialog(null, "Do you want a newgame?", "NewGame", JOptionPane.YES_NO_OPTION);
			if(result==JOptionPane.YES_OPTION) {
				new SelectPage();
				this.setVisible(false);
			}
		}
		if(obj==save) {

		}
		if(obj==exit) {
			int result = JOptionPane.showConfirmDialog(null, "Do you want to exit?", "Exit", JOptionPane.YES_NO_OPTION);
			if(result==JOptionPane.YES_OPTION) {
				System.exit(0);
			}
		}
		
	}

	@Override
	public void mouseClicked(MouseEvent e) {
		Object obj = e.getSource();
		if(obj==b0) {
			int result = JOptionPane.showConfirmDialog(null, "Do you want a goback?", "Back", JOptionPane.YES_NO_OPTION);
			if(result==JOptionPane.YES_OPTION) {
				new SelectPage();
				this.setVisible(false);
			}
		}
		else {
		for (int i = 0; i <5; i++) {
			for(int j=0;j<5;j++) {
				if(obj==gridlabel[i][j]) {
					String ss=gridlabel[i][j].getText();
					if(ss.equals("0")) {
						gridlabel[i][j].setText("1");
						gridlabel[i][j].setBackground(new Color(102,178,255));
						gridlabel[i][j].setForeground(new Color(102,178,255));
						break;
					}
					 if(ss.equals("-1")){
						gridlabel[i][j].setText("X");
						gridlabel[i][j].setForeground(Color.BLACK);
						countlife--;
						lifelabel .setText("Lifes: " + countlife);
						lifelabel.setFont(new Font("Comic Sans MS",Font.BOLD,21));
						if(countlife==0) {
							int result = JOptionPane.showConfirmDialog(null, "Try Again?", "Failed", JOptionPane.YES_NO_OPTION);
							if(result==JOptionPane.NO_OPTION) {
								System.exit(0);
							}
							if(result==JOptionPane.YES_OPTION) {
								new GamePage();
								this.setVisible(false);
							}
						}
					}
				}
			}
		}}
		int count=0;
		for(int i1=0; i1<5; i1++) {
			for(int j1=0; j1<5; j1++) {
				if(gridlabel[i1][j1].getText().equals("1")) {
					count++;
				}
			}
		}
		if(count==17) {
			int result = JOptionPane.showConfirmDialog(null, "Do you want to play a new game?", "Succeed", JOptionPane.YES_NO_OPTION);
			if(result==JOptionPane.YES_OPTION) {
				new SelectPage();
				this.setVisible(false);
			}
			if(result==JOptionPane.NO_OPTION) {
				System.exit(0);
			}
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
	public void mousePressed(MouseEvent e) {
		Object obj = e.getSource();
	

	}

	@Override
	public void mouseReleased(MouseEvent arg0) {
		// TODO Auto-generated method stub

	}



}

