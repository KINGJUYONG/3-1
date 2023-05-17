import java.awt.*;
import javax.swing.*;

public class Sprite { // 겹치는 코드등을 상속시키기 위해 만든 Sprite 클래스입니다.(부모 클래스)
    public int x, y;
    Image image;

    public Sprite() {
    }

    public int getX() { // x와 y를 가져오고, 이미지를 가져오고,
        return x;
    }

    public int getY() {
        return y;
    }

    public Image getImage() {
        return image;
    }

    public void loadImage(String name) { // Imageicon등을 사용하여 이미지를 불러오는 등의
        ImageIcon ii = new ImageIcon(name); // 간단하지만 겹치는 동작들을 모두 여기서 선언해줍니다.
        image = ii.getImage();

    }
}
