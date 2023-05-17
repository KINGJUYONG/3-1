import java.awt.*;

public class Missile extends Sprite { // Sprite 클래스를 상속받는 Missile 클래스입니다.
    private final int MISSILE_SPEED = 10; // 미사일의 속도를 10으로 고정합니다.
    int dx = 1, dy = 1; // dx, yx는 1로 설정해줍니다.
    Image image;
    boolean visible = true; // 부울 visible을 true로 설정해줍니다.

    public Missile(int x, int y) { // x,y좌표를 파라미터로 가지는 미사일 함수입니다.
        super(); // 스프라이트의 생성자를 호출합니다.
        loadImage("missile.png"); // loadimage함수를 이요하여 missile.png 파일을 가져오고
        this.x = x + 27; // 쉽의 왼쪽 끝에서 미사일이 발사되기에
        this.y = y - 30; // 미사일이 발사하는 위치를 우로 조정합니다.
    }

    public void move() { // move 함수입니다.
        y -= MISSILE_SPEED; // y - 미사일 스피드 연산을 해줍니다.
        if (y < 0) { // y좌표가 0 이하면
            visible = false; // 보이지 않게 합니다.
        }
    }
}