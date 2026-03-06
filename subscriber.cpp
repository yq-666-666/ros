#include "rclcpp/rclcpp.hpp"
#include "num_comm/msg/num.hpp"

// 订阅回调函数：接收到消息后执行
void num_callback(const num_comm::msg::Num & msg)
{
    // 计算求和
    int sum = msg.num1 + msg.num2;
    // 打印结果（VSCode会提示logger API）
    RCLCPP_INFO(rclcpp::get_logger("num_subscriber_node"), "【Jazzy+VSCode】订阅到：num1=%d, num2=%d | 求和结果：%d",
                msg.num1, msg.num2, sum);
}

int main(int argc, char * argv[])
{
    // ROS2初始化
    rclcpp::init(argc, argv);
    // 创建订阅方节点（简洁写法）
    auto node = rclcpp::Node::make_shared("num_subscriber_node");
    // 创建订阅者：绑定话题、队列大小、回调函数
    auto subscription = node->create_subscription<num_comm::msg::Num>(
        "num_topic", 10, num_callback);
    // 打印启动信息
    RCLCPP_INFO(node->get_logger(), "【Jazzy+VSCode】订阅方已启动，等待接收消息...");
    // 节点自旋
    rclcpp::spin(node);
    // 系统关闭
    rclcpp::shutdown();
    return 0;
}