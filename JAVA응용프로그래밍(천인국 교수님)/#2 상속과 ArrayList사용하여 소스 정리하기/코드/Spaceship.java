import java.util.ArrayList; 

public class Spaceship extends Sprite { // Sprite를 상속하는 Spaceship 클래스입니다. 
    ArrayList<Missile> list; // 미사일을 ArrayList로 선언해줍니다.

    public Spaceship() {
        x = 850; // 시작값을 850, 900으로 설정해주고
        y = 900;
        loadImage("ship.png"); // ship.png 이미지를 가져옵니다.
        list = new ArrayList<Missile>(); // 리스트에 어레이리스트 미사일 객체를 대입해줍니다.
    }

    public void move_left() {// 우주선의 좌표를 조정해주는 함수들입니다
        x -= 20;
        if (x < -15) { // 화면 밖으로 나가지 않게 화면 사이즈와 쉽의 크기를 고려해 제한을 걸어줍니다.
            x = -15;
        }
    }
    public void move_right() {
        x += 20;
        if (x > 1670) {
            x = 1670;
        }
    }
    public void move_up() {
        y -= 10;
        if (y < -38) {
            y = -38;
        }
    }
    public void move_down() {
        y += 10;
        if (y > 922) {
            y = 922;
        }
    }

    public void fire() { // fire 함수입니다.
        list.add(new Missile(x, y)); // 리스트에 새로운 미사일 객체를 추가해줍니다.
    }
}