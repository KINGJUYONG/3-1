import java.awt.Color; // 컬러 영역을 사용하기 위한 패키지
import java.awt.Dimension; // 컴포넌트의 높이와 폭을 캡슐화합니다.
import java.awt.Graphics; // 이미지 랜더링을 위해 사용하였습니다.
import java.awt.Image; // 그래픽 이미지를 표현하는 슈퍼클래스입니다.
import java.awt.Toolkit; // setvisible등을 사용하기 위해 추가하였습니다.
import java.io.File; // 파일 및 디렉토리 패스명을 표현합니다.

import javax.sound.sampled.AudioInputStream; // 외부의 오디오 파일을 받아오기 위해 사용한 패키지입니다.
import javax.sound.sampled.AudioSystem; // 받아온 오디오를 재생하기 위해 사용하였습니다.
import javax.sound.sampled.Clip; // 오디오를 스트리밍하는 것이 아닌 재생전에 로드하기 위해 사용하였습니다.
import javax.swing.ImageIcon; // 이미지를 가져오기 위해 사용하였습니다.
import javax.swing.JPanel; // 메인 프레임 위에 올리기 위해 사용하였습니다.

public class Board extends JPanel // Board라는 이름을 가진 클래스를 생성합니다.
        implements Runnable { // 러너블 객체로 생성하여 자동으로 쓰레드를 할당하게 합니다.

    private final int B_WIDTH = 1400; // 창 가로
    private final int B_HEIGHT = 1400; // 창 세로
    private final int INITIAL_X = 0; // 시작하는 X축
    private final int INITIAL_Y = 140; // 시작하는 Y축
    private int DELAY = 10; // 화면 갱신시간을 10으로 설정합니다.

    private Image star, back, expl, astr; // 이미지가 들어갈 변수들을 선언해줍니다.
    private Thread animator; // 쓰레드를 할당받는 animator를 선언합니다.
    private int x, y, a, b, c, d; // 각 사진들의 좌표가 될 변수들입니다.

    public Board() {
        initBoard(); // 아래의 initBoard 함수를 호출합니다.
    }

    private void loadImage() { // 이미지를 로드하는 함수입니다.
        ImageIcon ii = new ImageIcon("rocket2.png"); // ImageIcon메서드를 사용하여 각각의 이미지를 객체로 생성해주고
        ImageIcon ba = new ImageIcon("background.jpg");
        ImageIcon ex = new ImageIcon("explosion.png");
        ImageIcon as = new ImageIcon("astronaut.png");
        star = ii.getImage(); // getImage를 통해 각 이미지를 변수에 할당합니다.
        back = ba.getImage();
        expl = ex.getImage();
        astr = as.getImage();
    }

    private void initBoard() {
        setBackground(Color.BLACK); // 배경 색상을 검정색으로 설정해주고
        setPreferredSize(new Dimension(B_WIDTH, B_HEIGHT)); // 위에서 미리 정해둔 가로와 세로 길이만큼 창의 크기를 설정해줍니다.
        setDoubleBuffered(true); // 버퍼를 사용하여 페인팅하게 합니다.

        loadImage(); // loadImage함수를 호출합니다.

        x = INITIAL_X; // 이후 x와 y좌표를 설정해준 값으로 바꿔줍니다.
        y = INITIAL_Y;
    }

    @Override
    public void addNotify() { // addNotify 함수입니다.
        super.addNotify();

        animator = new Thread(this); // 애니메이터에 쓰레드를 할당해주고
        animator.start(); // 애니메이터가 동작하게 합니다.
    }

    private void drawBack(Graphics g) {
        g.drawImage(back, 0, 0, this); // 이미지의 정보가 저장된 변수와 좌표를 파라미터로 하여 이미지를 생성합니다.
        Toolkit.getDefaultToolkit().sync(); // 그래픽 상태를 동기화시킵니다.
    }
    private void drawAstr(Graphics g) {
        g.drawImage(astr, c, d, this);
        Toolkit.getDefaultToolkit().sync();
    }
    private void drawStar(Graphics g) {

        g.drawImage(star, x, y, this);
        Toolkit.getDefaultToolkit().sync();
    }
    private void drawExpl(Graphics g) {
        g.drawImage(expl, a, b, this);
        Toolkit.getDefaultToolkit().sync();
    }

    @Override
    public void paintComponent(Graphics g) {
        super.paintComponent(g);

        drawBack(g); // 위에서 작성한 함수들을 일괄적으로 호출합니다.(이미지 생성)
        drawAstr(g);
        drawStar(g);
        drawExpl(g);
    }

    private void cycle() { // 반복될 함수입니다. 애니메이션의 진행 상황을 결정합니다.
        if (x < 120) { // 시작부터 X가 120이 되기 전까지
            x += 1; // 로켓이 X,Y축으로 1씩 움직이고
            y += 1;
            a = 9999; // 폭발효과는 창에서 보이지 않게 합니다.
            b = 9999;
            c = 600; // 우주비행사는 해당 위치에 고정됩니다.
            d = 600;
        }
        if (x >= 120 && y <= 400) {
            x -= 4; // X가 120 이상이고 Y가 400 이하일때
            x += 1; // X를 4만큼 빼고 1만큼 더해주며(좌우로 흔들리며)
            y += 4; // 아래로 4만큼 내려갑니다
        }
        if (x == 75) { // x축이 75가 됐을때(로켓의 결함이 생겼을 때)
            try {
                AudioInputStream ais = AudioSystem.getAudioInputStream(new File("rocket.wav")); // ROCKET.WAV파일을 가져와 ais에 저장해주고
                Clip clip = AudioSystem.getClip(); // 해당 음성파일을 미리 로드합니다.
                clip.stop();
                clip.open(ais); // 음성 파일을 재생합니다.
                clip.start();
            } catch (Exception ex) { // 어떠한 예외에도 동작하도록 해주었습니다.
            }
        }
        if (y >= 400) { // y가 400이상 가면
            a = -170; // 폭발효과가 지정된 위치에 나타나고
            b = 300;
            c += 5; // 우주비행사가 충격에 날아갑니다.
            d += 5;
            x += 5; // 로켓은 더 빠른 속도로 움직이게 됩니다.
            y -= 3;
            DELAY = 3; // 지연효과를 적게 하여 더 빨리 움직이도록 합니다.
        }
        if (x > B_WIDTH + 50) { // 로켓이 화면에서 완전히 사라지면
            y = INITIAL_Y; // X와 Y를 초기값으로 다시 설정해주고
            x = INITIAL_X;
            DELAY = 10; // 지연도 초기값으로 돌아갑니다.
            try {
                Thread.sleep(2000); // 이후 2000만큼 쉬었다가 다시 반복됩니다.
            } catch (Exception e) {
            }
        }
    }


    @Override
    public void run() {

        long beforeTime, timeDiff, sleep; // 현재시간, 시차, 쉬는시간 변수입니다.

        beforeTime = System.currentTimeMillis(); // 현재시간을 변수에 저장해줍니다.

        while (true) { // 무한 반복문입니다.

            cycle(); // 위의 cycle함수를 호출합니다.
            repaint(); // repaint함수를 호출합니다.

            timeDiff = System.currentTimeMillis() - beforeTime; // 시차 = 호출한 현재시간 - 앞서 저장한 현재시간
            sleep = DELAY - timeDiff; // 딜레이 - 시차만큼 sleep에 저장해줍니다.

            if (sleep < 0) { // sleep이 음수일 경우
                sleep = 2; // sleep을 2로 설정해줍니다.
            }

            try {
                Thread.sleep(sleep); // Thread를 sleep만큼 쉬게 합니다.
            } catch (InterruptedException e) {
                System.out.println("Interrupted: " + e.getMessage()); // 인터럽트가 발생하면 경고창을 출력합니다.
            }
            beforeTime = System.currentTimeMillis(); // 다시 현재시간을 설정해줍니다.
        }
    }
}