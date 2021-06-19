//음악도 넣을거다


import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.io.File;
import java.io.FileInputStream;
import java.io.InputStream;
import java.net.URL;

import javax.swing.*;

import java.io.*;


public class Howto extends JFrame implements MouseListener  {
	private JLabel backlabel;
	public Howto() {
		setTitle("HOWTO");
		setSize(500,600);
		setLocationRelativeTo(null); //좌표지정해주는거도잇음


		Container c= getContentPane();
		c.setLayout(null);

		URL url2 = SelectPage.class.getResource("img/back.png");
		ImageIcon backb = new ImageIcon(url2);
		Image image1= backb.getImage();
		Image newimg1 = image1.getScaledInstance(20, 20, Image.SCALE_SMOOTH);
		backb= new ImageIcon(newimg1);

		backlabel = new JLabel(backb);
		backlabel.setBounds(2, 2, 20, 20);
		backlabel.addMouseListener(this);
		URL url1 = SelectPage.class.getResource("img/howto.png");
		ImageIcon howto = new ImageIcon(url1);
		Image image=howto.getImage();
		Image newimg = image.getScaledInstance(290, 380, Image.SCALE_SMOOTH);
		howto= new ImageIcon(newimg);
		JLabel howtodo = new JLabel(howto);
		howtodo.setBounds(100,80,300,400);
		c.add(backlabel);
		c.add(howtodo);
		setVisible(true);
	}

	public static void main(String[] args) {

	}

	@Override
	public void mouseClicked(MouseEvent e) {
		// TODO Auto-generated method stub
		Object obj =e.getSource();
		if(obj==backlabel)
		{new MainPage(null);
		this.setVisible(false);}
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


}


