import sys, tty, termios
import rclpy
from rclpy.node import Node
from led_control_msgs.msg import LedStatus

class KeyboardLED(Node):
    def __init__(self):
        super().__init__('keyboard_led')
        self.status = LedStatus(red=False, green=False, yellow=False)
        self.pub = self.create_publisher(LedStatus, 'led_cmd', 10)

    def run(self):
        self.pub.publish(self.status) # reset to all OFF at start

        print("Press 'a'=All ON, 'o'=All OFF, 'r'=Toggle Red, 'g'=Toggle Green, 'y'=Toggle Yellow, 'q'=quit")

        fd = sys.stdin.fileno()
        old = termios.tcgetattr(fd)
        tty.setraw(fd)

        try:
            while rclpy.ok():
                ch = sys.stdin.read(1)
                if ch == 'a':
                    self.status.red = True
                    self.status.green = True
                    self.status.yellow = True
                elif ch == 'o':
                    self.status.red = False
                    self.status.green = False
                    self.status.yellow = False
                elif ch == 'r':
                    self.status.red = not self.status.red
                elif ch == 'g':
                    self.status.green = not self.status.green
                elif ch == 'y':
                    self.status.yellow = not self.status.yellow
                elif ch == 'q':
                    break

                self.pub.publish(self.status)
        finally:
            termios.tcsetattr(fd, termios.TCSADRAIN, old)

def main():
    rclpy.init()

    node = KeyboardLED()
    node.run()
    node.destroy_node()

    rclpy.shutdown()

if __name__ == '__main__':
    main()
