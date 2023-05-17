import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.Toolkit;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;

import java.awt.*;
import javax.swing.*;

public class Board extends JPanel implements ActionListener, KeyListener { // 액션리스너, 키 리스너가 적용된 Board 클래스입니다. JPanel을
																			// 상속받습니다.

	private Timer timer; // 해당 클래스에서만 사용할 Timer 변수를 선언합니다.
	Spaceship ship; // ship 변수를 선언해줍니다.
	private final int DELAY = 0; // DELAY변수의 수정을 편하게 하기 위해 따로 선언해줍니다.

	Image Background; // 이미지 변수 Background를 선언해줍니다.

	public Board() {
		addKeyListener(this); // 키리스너가 이곳을 참조하도록 합니다.
		setFocusable(true); // Focusable을 true로 설정해줍니다.
		ship = new Spaceship(); // Spaceship객체 ship을 선언해줍니다.
		timer = new Timer(DELAY, this); // DELAY ms만큼의 지연을 가지는 타이머를 설정해줍니다.
		timer.start();
		ImageIcon back = new ImageIcon("background.jpg"); // background.jpg파일을 가져와 back 변수에 저장하고
		Background = back.getImage(); // back의 이미지를 getImage를 통해 가져와 Background에 저장해줍니다.
	}

	@Override
	public void paintComponent(Graphics g) { // paintComponent함수입니다.
		super.paintComponent(g); // paintComponenet함수는 Graphics의 생성자를 실행합니다.
		Graphics2D g2d = (Graphics2D) g; // g2d변수에 Graphics2D 객체 g를 저장해줍니다.
		g.drawImage(Background, 0, 0, null); // 앞서 가져온 배경사진 그림을 0,0 위치에 올려줍니다.
		g2d.drawImage(ship.getImage(), ship.getX(), ship.getY(), this); // ship의 사진과 x,y좌표를 가져와 그려줍니다.
		for (Missile m : ship.list) { // ship 리스트에 들어있는 미사일을 전부 꺼내줍니다.
			g2d.drawImage(m.getImage(), m.getX(), m.getY(), this); // 꺼내준 미사일을 모두 그려줍니다.
		}
		Toolkit.getDefaultToolkit().sync(); // 그래픽 상태를 동기화합니다.
	}

	@Override
	public void actionPerformed(ActionEvent e) { // actionPerformed 함수입니다.
		for (Missile m : ship.list) { // 미사일(그려진)을 꺼내어
			m.move(); // 움직이도록 합니다.
		}
		repaint(); // repaint 해줍니다.
	}

	@Override
	public void keyReleased(KeyEvent e) { // 키에서 손을 떼었을때는 따로 설정해주지 않았습니다.
	}

	@Override
	public void keyPressed(KeyEvent e) { // KeyEvent에서 받아온 정보를 e에 저장해주고
		if (e.getKeyCode() == KeyEvent.VK_LEFT) // 그 정보의 코드가 VK_LEFT와 같다면
			ship.move_left(); // ship을 좌측으로 움직이게 하는 함수를 호출 합니다.
		if (e.getKeyCode() == KeyEvent.VK_RIGHT) // 아래의 기능은 모두 같습니다.
			ship.move_right();
		if (e.getKeyCode() == KeyEvent.VK_UP)
			ship.move_up();
		if (e.getKeyCode() == KeyEvent.VK_DOWN)
			ship.move_down();
		if (e.getKeyCode() == KeyEvent.VK_SPACE)
			ship.fire();
	}

	@Override
	public void keyTyped(KeyEvent arg0) {
	}
}