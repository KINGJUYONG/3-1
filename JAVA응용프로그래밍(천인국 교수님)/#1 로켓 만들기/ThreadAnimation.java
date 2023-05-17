import java.awt.EventQueue;
import javax.swing.JFrame;

public class ThreadAnimationExample extends JFrame {
    public ThreadAnimationExample() {
        initUI();
    }
    private void initUI() {
        add(new Board());

        setResizable(false); // 창 사이즈를 조절할 수 없게 합니다.
        pack();
        
        setTitle("Star"); // 프로그램의 이름을 Star로 설정합니다.
        setLocationRelativeTo(null); // 서로의 위치가 간섭되지 않도록 하고
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE); // 창을 닫았을 때 프로세스도 함께 닫히도록 합니다.
    }

    public static void main(String[] args) {
        
        EventQueue.invokeLater(new Runnable() {
            
            @Override
            public void run() {                
                JFrame ex = new ThreadAnimationExample();
                ex.setVisible(true);                
            }
        });
    }
}