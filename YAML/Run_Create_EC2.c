#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main()
{
    // Mở file log
    FILE *logFile = fopen("log.txt", "w");
    if (logFile == NULL)
    {
        perror("Error opening log file");
        return 1;
    }
    // Lấy đường dẫn thư mục hiện tại
    char current_dir[1024];
    if (getcwd(current_dir, sizeof(current_dir)) == NULL)
    {
        fprintf(logFile, "getcwd() error\n");
        fclose(logFile);
        return 1;
    }
    // Chuyển con trỏ sang thư viện hiện tại
    if (chdir(current_dir) != 0)
    {
        fprintf(logFile, "chdir() error\n");
        fclose(logFile);
        return 1;
    }
    // Chạy lệnh khởi tạo Stack tên test
    char *command = "aws cloudformation create-stack --stack-name test --template-body file://ec2.yaml";
    if (system(command) == -1)
    {
        fprintf(logFile, "Error creating stack\n");
        fclose(logFile);
        return 1;
    }
    // Hiển thị các thông số của Stack sau khi khởi tạo thành công
    if (system("aws cloudformation wait stack-create-complete --stack-name test") == -1)
    {
        fprintf(logFile, "Error waiting for stack creation to complete\n");
        fclose(logFile);
        return 1;
    }
    // Mở file dữ liệu StackStatus
    char status[] = "aws cloudformation describe-stacks --stack-name test --query \"Stacks[].{\\\"Status\\\":StackStatus}\" --output text";
    FILE *fp = popen(status, "r");
    if (fp == NULL)
    {
        fprintf(logFile, "Error opening pipe\n");
        fclose(logFile);
        return 1;
    }
    // Lấy giá trị của StackStatus
    char stack_status[1024] = {0};
    if (fgets(stack_status, sizeof(stack_status), fp) == NULL)
    {
        fprintf(logFile, "Error reading pipe\n");
        pclose(fp);
        fclose(logFile);
        return 1;
    }
    // Đóng file
    pclose(fp);
    // Ghi log
    stack_status[strcspn(stack_status, "\n")] = 0;
    if (strcmp(stack_status, "CREATE_COMPLETE") != 0)
    {
        fprintf(logFile, "Stack creation failed with status: %s\n", stack_status);
        fclose(logFile);
        return 1;
    }
    else
    {
        fprintf(logFile, "Stack creation with status: %s\n", stack_status);
    }
    char info[] = "aws cloudformation describe-stacks --stack-name test --output json";
    if (system(info) == -1)
    {
        fprintf(logFile, "Error information stacks\n");
        fclose(logFile);
        return 1;
    }
    // In ra địa chỉ Public IP
    char output[] = "aws cloudformation describe-stacks --stack-name test --query \"Stacks[0].Outputs[?OutputKey=='InstancePublicIp'].OutputValue | [0]\"";
    if (system(output) == -1)
    {
        fprintf(logFile, "Error describing stacks\n");
        fclose(logFile);
        return 1;
    }

    fclose(logFile);
    while (1)
    {
    }

    return 0;
}
