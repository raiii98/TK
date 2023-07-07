# Set up Squid proxy server

### 1. Thiết bị cần thiết:
- Máy chủ VPS đã cài hệ điều hành ubuntu

### 2. Cài đặt proxy server trên ubuntu:
Step 1: Chuyển sang quyền root

    sudo su

Step 2: Cập nhập một số gói tin cần thiết

    sudo apt update
    sudo apt upgrade
Step 3: Tải tập tin cài đặt của Squidproxy server

    wget https://raw.githubusercontent.com/serverok/squid-proxy-installer/master/squid3-install.sh
Kiểm tra tập tin:

    ls -la 
Step 4: Chạy file script đã tải

    sudo bash squid3-install.sh
Step 5: Thêm xác thực cho proxy

    sudo squid-add-user
Nhập tài khoản và mật khẩu
Step 6: Kiểm tra cổng mạng của proxy trên server

    apt install net-tools
    netstat -lntp         
Port mặc định của proxy trên server là 3128
Step 7: Đổi port của proxy

    