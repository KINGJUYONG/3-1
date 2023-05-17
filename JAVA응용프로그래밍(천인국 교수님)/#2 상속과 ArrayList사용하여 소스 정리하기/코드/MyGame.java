import javax.swing.JFrame;

public class MyGame extends JFrame {

    public MyGame() { // MyGame의 생성자입니다.
        initUI(); // 아래의 initUI함수를 호출합니다.
    }

    private void initUI() {
        add(new Board()); // Board 객체를 생성하여 add 해주고
        setSize(1824, 1026); // 창의 사이즈를 조절합니다.
        setTitle("Star"); // 프로그램의 이름을 설정해주고
        setVisible(true); // 보이도록 해줍니다.
        this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE); // 창을 닫을시 프로세스도 함께 종료되도록 하는 옵션을 설정해줍니다.
    }

    public static void main(String[] args) {
        MyGame ex = new MyGame(); // 메인에서는 MyGame 객체를 생성해줍니다.
    }
}
