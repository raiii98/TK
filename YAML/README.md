# Dự án CloudFormation

## Mô tả
Dự án này sử dụng ngôn ngữ lập trình C, YAML và AWS CloudFormation để tự động tạo và xóa stack EC2 trên AWS.

## Các tệp quan trọng
* `ec2.yaml`: Đây là tệp CloudFormation template, dùng để mô tả cấu trúc và tài nguyên của stack EC2.
* `Run_Create_EC2.c`: Chương trình này, được viết bằng ngôn ngữ C, sử dụng `ec2.yaml` để tạo một stack CloudFormation trên môi trường AWS CLI và ghi log.
* `Run_Del_EC2.c`: Chương trình này, cũng được viết bằng ngôn ngữ C, được sử dụng để xóa stack CloudFormation.

## Cài đặt
Để cài đặt và chạy dự án này, bạn cần cài đặt AWS CLI và compiler C (như gcc) trên máy của bạn. Sau đó, bạn có thể chạy các chương trình C bằng lệnh sau:

Biên dịch:

    gcc Run_Create_EC2.c -o Create_EC2

Chạy chương trình:

    ./createCreate_EC2

Biên dịch:

    gcc Run_Del_EC2.c -o Delete_EC2

Chạy chương trình:

    ./Delete_EC2

Vui lòng thay đổi các thông số trong tệp `ec2.yaml` để phù hợp với yêu cầu của bạn.

## Lưu ý
Hãy chắc chắn rằng bạn đã cấu hình AWS CLI với đúng thông tin trước khi chạy các chương trình này.
