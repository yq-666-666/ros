#include "rclcpp/rclcpp.hpp"
// 自定义消息头文件（VSCode会自动提示，Jazzy编译后生成）
#include "num_comm/msg/num.hpp"

// 定时器周期：1秒发布一次
using namespace std::chrono_literals;

// 发布方节点类：继承rclcpp::Node（ROS2 C++基类）
class NumPublisher : public rclcpp::Node
{
public:
    // 构造函数：初始化节点名、计数器、发布者、定时器
    NumPublisher() : Node("num_publisher_node"), count_(0)
    {
        // 创建发布者：话题名num_topic，队列大小10（消息缓存）
        publisher_ = this->create_publisher<num_comm::msg::Num>("num_topic", 10);
        // 创建定时器：绑定回调函数，1秒触发一次
        timer_ = this->create_wall_timer(1s, std::bind(&NumPublisher::timer_callback, this));
        // 日志打印：发布方启动成功（Jazzy日志API与Humble一致）
        RCLCPP_INFO(this->get_logger(), "【Jazzy+VSCode】发布方已启动，开始发布num1/num2！");
    }

private:
    // 定时器回调函数：生成并发布消息
    void timer_callback()
    {
        // 创建自定义消息对象（VSCode会提示成员变量num1/num2）
        auto msg = num_comm::msg::Num();
        // 消息赋值：num1自增，num2=num1+5（方便求和验证）
        msg.num1 = count_++;
        msg.num2 = count_ + 5;
        // 打印发布的数值
        RCLCPP_INFO(this->get_logger(), "发布：num1=%d, num2=%d", msg.num1, msg.num2);
        // 发布消息到话题
        publisher_->publish(msg);
    }

    // 成员变量（VSCode会提示类型补全）
    rclcpp::TimerBase::SharedPtr timer_;
    rclcpp::Publisher<num_comm::msg::Num>::SharedPtr publisher_;
    size_t count_;
};

// 主函数：ROS2节点入口
int main(int argc, char * argv[])
{
    // ROS2系统初始化（Jazzy必须第一步执行）
    rclcpp::init(argc, argv);
    // 节点自旋：保持运行，处理回调
    rclcpp::spin(std::make_shared<NumPublisher>());
    // 系统关闭
    rclcpp::shutdown();
    return 0;
}