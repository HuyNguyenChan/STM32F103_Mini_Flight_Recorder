# STM32F103 Mini Flight Recorder



## 1. Dự án này làm gì?

Dự án dùng board STM32F103C8T6 để đọc cảm biến gia tốc/con quay MPU6050, ghi dữ liệu vào chip nhớ flash W25Q64, và xuất dữ liệu ra máy tính qua UART.

Chức năng chính:

- Bấm nút RECORD để bắt đầu hoặc dừng ghi dữ liệu.
- Khi đang ghi, đèn LED xanh sáng.
- Dữ liệu cảm biến được in ra UART và đồng thời lưu vào W25Q64.
- Bấm nút DUMP để xuất toàn bộ dữ liệu đã lưu ra UART.
- Giữ nút DUMP khoảng 3 giây để xóa toàn bộ dữ liệu trong W25Q64.

Firmware được viết bare-metal trong `main.c`, thao tác trực tiếp với thanh ghi của STM32, không dùng HAL.

## 2. Cần chuẩn bị gì?

### Phần cứng

Bạn cần:

- 1 board STM32F103C8T6, thường gọi là Blue Pill.
- 1 module MPU6050.
- 1 module flash SPI W25Q64 hoặc W25Qxx tương thích 3.3 V.
- 1 mạch nạp ST-Link V2.
- 1 USB to TTL UART mức 3.3 V, ví dụ CH340, CP2102, FT232.
- 2 nút nhấn.
- 1 LED và 1 điện trở khoảng 220 ohm đến 1 k ohm, nếu board chưa có LED ngoài theo chân PB0.
- Dây cắm, breadboard.
- Cáp USB.

Lưu ý quan trọng: STM32F103, MPU6050 và W25Q64 dùng mức logic 3.3 V. Không cấp hoặc nối tín hiệu 5 V trực tiếp vào các chân này.

### Phần mềm

Cài trên máy tính Windows:

- Keil uVision 5.
- ARM Compiler 6 trong Keil.
- Gói device pack `Keil.STM32F1xx_DFP`, project đang dùng pack `2.4.1`.
- Driver ST-Link.
- Phần mềm terminal serial như PuTTY, Tera Term, RealTerm hoặc Serial Monitor khác.

Nếu dùng STM32CubeProgrammer để nạp file `.hex`, cài thêm STM32CubeProgrammer.

## 3. Sơ đồ nối dây

### Nguồn chung

Tất cả module phải dùng chung GND.

| Thiết bị | Chân | Nối tới |
| --- | --- | --- |
| STM32 | 3.3V | VCC của MPU6050, VCC của W25Q64 |
| STM32 | GND | GND của MPU6050, W25Q64, ST-Link, USB-TTL |

Không dùng chân 5V để cấp cho MPU6050 hoặc W25Q64 nếu module của bạn không chắc chắn hỗ trợ 5 V.

### MPU6050 qua I2C1

| MPU6050 | STM32F103C8T6 |
| --- | --- |
| VCC | 3.3V |
| GND | GND |
| SCL | PB6 |
| SDA | PB7 |
| AD0 | GND, để địa chỉ I2C là `0x68` |

Nhiều module MPU6050 đã có điện trở kéo lên I2C. Nếu module của bạn không có, cần thêm điện trở kéo lên khoảng 4.7 k ohm từ SCL lên 3.3 V và từ SDA lên 3.3 V.

### W25Q64 qua SPI1

| W25Q64 | STM32F103C8T6 |
| --- | --- |
| VCC | 3.3V |
| GND | GND |
| CS / NSS | PA4 |
| SCK / CLK | PA5 |
| DO / MISO | PA6 |
| DI / MOSI | PA7 |
| WP | 3.3V |
| HOLD | 3.3V |

### UART để xem dữ liệu trên máy tính

| USB-TTL | STM32F103C8T6 |
| --- | --- |
| GND | GND |
| RXD | PA9, USART1_TX |
| TXD | PA10, USART1_RX |

Không nối chân 5V của USB-TTL vào STM32 nếu board đã được cấp nguồn riêng hoặc đang cấp nguồn qua ST-Link/USB.

Thông số UART:

- Baud rate: `9600`
- Data bits: `8`
- Parity: `None`
- Stop bits: `1`
- Flow control: `None`

### Nút nhấn và LED

| Chức năng | STM32F103C8T6 | Cách nối |
| --- | --- | --- |
| Nút RECORD | PA0 | Một chân nút vào PA0, chân còn lại xuống GND |
| Nút DUMP / ERASE | PA1 | Một chân nút vào PA1, chân còn lại xuống GND |
| LED xanh | PB0 | PB0 -> điện trở -> LED -> GND |

Trong code đã bật pull-up nội cho PA0 và PA1, nên khi không bấm nút chân sẽ ở mức 1, khi bấm nút sẽ xuống GND.

## 4. Cấu trúc thư mục

Các file quan trọng:

```text
main.c
STM32F103_Mini_Flight_Recorder.uvprojx
STM32F103_Mini_Flight_Recorder.uvoptx
RTE/
DebugConfig/
Objects/
Listings/
```

Ý nghĩa:

- `main.c`: toàn bộ chương trình chính.
- `STM32F103_Mini_Flight_Recorder.uvprojx`: file project để mở bằng Keil uVision.
- `STM32F103_Mini_Flight_Recorder.uvoptx`: cấu hình giao diện/debug của Keil.
- `RTE/`: file startup và cấu hình thiết bị do Keil tạo.
- `Objects/`: nơi Keil thường xuất file build.
- `Listings/`: nơi Keil thường xuất file listing.

## 5. Mở project bằng Keil

1. Mở Keil uVision 5.
2. Chọn `Project` -> `Open Project...`.
3. Chọn file `STM32F103_Mini_Flight_Recorder.uvprojx`.
4. Nếu Keil hỏi cài device pack cho STM32F103C8, chọn cài pack STM32F1xx.
5. Nhìn cây project bên trái.

Nếu chưa thấy `main.c` trong `Source Group 1`, hãy thêm thủ công:

1. Chuột phải vào `Source Group 1`.
2. Chọn `Add Existing Files to Group 'Source Group 1'...`.
3. Chọn `main.c`.
4. Nếu project thiếu startup file, thêm tiếp:
   - `RTE/Device/STM32F103C8/startup_stm32f10x_md.s`
   - `RTE/Device/STM32F103C8/system_stm32f10x.c`

## 6. Cấu hình project trước khi build

Trong Keil, mở `Project` -> `Options for Target 'Target 1'`.

Kiểm tra các mục sau:

- Tab `Device`: chọn `STM32F103C8`.
- Tab `Target`:
  - `IROM1`: Start `0x08000000`, Size `0x10000`.
  - `IRAM1`: Start `0x20000000`, Size `0x5000`.
  - `Xtal`: nếu dùng Blue Pill phổ biến, đặt `8.0 MHz`.
- Tab `C/C++ (AC6)`: dùng ARM Compiler 6.
- Tab `Output`:
  - Có thể bật `Create HEX File` nếu muốn tạo file `.hex` để nạp bằng công cụ ngoài Keil.
- Tab `Debug`:
  - Chọn `ST-Link Debugger` nếu nạp/debug bằng ST-Link.
- Tab `Utilities`:
  - Chọn `ST-Link Debugger`.
  - Bấm `Settings`, kiểm tra flash algorithm cho STM32F10x medium density.

## 7. Build chương trình

Trong Keil:

1. Bấm `Build` hoặc nhấn `F7`.
2. Nhìn cửa sổ `Build Output`.
3. Nếu thành công, Keil sẽ báo `0 Error(s)`.

Nếu gặp lỗi thường gặp:

- Thiếu pack STM32F1xx: mở `Pack Installer`, tìm `STM32F1xx_DFP` và cài.
- Không tìm thấy startup file: thêm `startup_stm32f10x_md.s` vào project.
- Không tìm thấy `main`: kiểm tra đã thêm `main.c` vào `Source Group 1`.
- Lỗi compiler: kiểm tra đang dùng ARM Compiler 6 như project cấu hình.

## 8. Nạp chương trình vào STM32

### Cách 1: Nạp trực tiếp bằng Keil

1. Cắm ST-Link vào máy tính.
2. Nối ST-Link với STM32:

| ST-Link | STM32F103C8T6 |
| --- | --- |
| 3.3V | 3.3V |
| GND | GND |
| SWDIO | SWDIO |
| SWCLK | SWCLK |

3. Trong Keil, bấm `Download` hoặc nhấn `F8`.
4. Nếu nạp thành công, reset lại board.

### Cách 2: Nạp file hex bằng STM32CubeProgrammer

1. Trong Keil, bật `Create HEX File`.
2. Build lại project.
3. Mở STM32CubeProgrammer.
4. Kết nối ST-Link.
5. Chọn file `.hex` được Keil tạo.
6. Bấm `Download`.

## 9. Chạy và kiểm tra

1. Cắm USB-TTL vào máy tính.
2. Mở PuTTY, Tera Term hoặc phần mềm terminal.
3. Chọn đúng COM port của USB-TTL.
4. Cấu hình `9600 8N1`.
5. Reset board STM32.
6. Nếu mọi thứ đúng, terminal sẽ hiện:

```text
START
```

### Ghi dữ liệu

1. Bấm nút RECORD ở PA0 một lần.
2. Terminal sẽ hiện:

```text
RECORD ON
```

3. LED ở PB0 sáng.
4. Terminal bắt đầu in dữ liệu dạng:

```text
AX:123 AY:-45 AZ:16000 GX:10 GY:-8 GZ:3
```

5. Dữ liệu này cũng được ghi vào W25Q64.
6. Bấm RECORD lần nữa để dừng. Terminal sẽ hiện:

```text
RECORD OFF
```

### Xuất dữ liệu đã lưu

Bấm nhanh nút DUMP ở PA1.

Terminal sẽ hiện:

```text
DUMP START
...
DUMP END BYTES:... SAMPLES:...
```

Phần giữa là dữ liệu đã lưu trong flash.

### Xóa dữ liệu đã lưu

Giữ nút DUMP ở PA1 khoảng 3 giây.

Terminal sẽ hiện:

```text
ERASE START
ERASE DONE
```

Sau khi xóa, bộ đếm địa chỉ ghi và số mẫu được đưa về 0.

## 10. Tần suất lấy mẫu

Timer 2 tạo ngắt mỗi 10 ms. Code đặt `SAMPLE_INTERVAL_TICKS` là `100`, nghĩa là lấy 1 mẫu sau mỗi 100 tick.

Vì vậy tần suất lấy mẫu hiện tại là:

```text
100 tick x 10 ms = 1000 ms = 1 giây / mẫu
```

Nếu muốn lấy mẫu nhanh hơn, sửa trong `main.c`:

```c
#define SAMPLE_INTERVAL_TICKS 100U
```

Ví dụ:

- `50U`: khoảng 0.5 giây/mẫu.
- `10U`: khoảng 0.1 giây/mẫu.
- `1U`: khoảng 0.01 giây/mẫu.

Không nên đặt quá nhanh khi mới thử, vì UART 9600 baud và ghi flash có giới hạn tốc độ.

## 11. Các chân đang dùng trong code

| Chức năng | Chân STM32 |
| --- | --- |
| RECORD button | PA0 |
| DUMP / ERASE button | PA1 |
| W25Q64 CS | PA4 |
| W25Q64 SCK | PA5 |
| W25Q64 MISO | PA6 |
| W25Q64 MOSI | PA7 |
| USART1 TX | PA9 |
| USART1 RX | PA10 |
| LED xanh | PB0 |
| MPU6050 SCL | PB6 |
| MPU6050 SDA | PB7 |

## 12. Cách hiểu nhanh chương trình

Thứ tự chạy trong `main()`:

1. Cấu hình clock 72 MHz từ thạch anh ngoài 8 MHz.
2. Cấu hình GPIO.
3. Cấu hình USART1 để gửi dữ liệu về máy tính.
4. Cấu hình I2C1 để giao tiếp MPU6050.
5. Cấu hình SPI1 để giao tiếp W25Q64.
6. Mở khóa bảo vệ ghi của W25Q64.
7. Khởi động MPU6050.
8. Cấu hình TIM2 để tạo nhịp lấy mẫu.
9. Vòng lặp chính liên tục đọc nút, lấy mẫu, in UART và ghi flash.

Các khối hàm chính:

- `Clock_Init_72MHz_HSE8()`: cấu hình clock hệ thống.
- `GPIO_Init()`: cấu hình nút, LED.
- `USART1_Init()`: cấu hình UART 9600 baud.
- `I2C1_Init()`: cấu hình I2C cho MPU6050.
- `SPI1_Init()`: cấu hình SPI cho W25Q64.
- `MPU6050_ReadSample()`: đọc gia tốc và con quay.
- `Recorder_WriteLog()`: ghi dữ liệu vào flash.
- `Recorder_DumpText()`: đọc flash và xuất ra UART.
- `Recorder_EraseAll()`: xóa toàn bộ flash.
- `Buttons_Task()`: xử lý nút bấm.

## 13. Khắc phục sự cố

### Terminal không hiện `START`

Kiểm tra:

- Đã nạp chương trình thành công chưa.
- Board có được cấp nguồn không.
- Đã nối GND chung giữa STM32 và USB-TTL chưa.
- USB-TTL RXD đã nối PA9 chưa.
- Baud rate đã đặt `9600` chưa.
- Có chọn đúng COM port không.

### Không thấy dữ liệu thay đổi

Kiểm tra:

- MPU6050 đã nối đúng PB6/PB7 chưa.
- VCC của MPU6050 là 3.3 V chưa.
- AD0 đã nối GND chưa.
- Module MPU6050 có điện trở kéo lên I2C chưa.

### Bấm nút không có phản ứng

Kiểm tra:

- Nút RECORD nối giữa PA0 và GND.
- Nút DUMP nối giữa PA1 và GND.
- Không nối nút lên 3.3 V theo kiểu ngoài, vì code đang dùng pull-up nội và bấm là kéo xuống GND.

### Ghi flash nhưng dump không có dữ liệu

Kiểm tra:

- W25Q64 đã nối đúng SPI1 chưa.
- WP và HOLD đã kéo lên 3.3 V chưa.
- GND của W25Q64 có chung với STM32 không.
- Dây SPI có quá dài hoặc lỏng không.

### Keil báo không nạp được

Kiểm tra:

- ST-Link đã cài driver chưa.
- SWDIO, SWCLK, GND nối đúng chưa.
- Trong `Options for Target` -> `Debug` đã chọn `ST-Link Debugger` chưa.
- Board có đang được cấp nguồn ổn định không.

## 14. Gợi ý quy trình làm từ đầu

Nếu bạn mới hoàn toàn, hãy làm theo thứ tự này:

1. Chỉ nối STM32 với ST-Link.
2. Mở Keil, build và nạp được chương trình.
3. Nối USB-TTL, mở terminal, thấy chữ `START`.
4. Nối 2 nút nhấn, bấm RECORD thấy `RECORD ON/OFF`.
5. Nối MPU6050, bấm RECORD thấy dữ liệu AX/AY/AZ/GX/GY/GZ.
6. Nối W25Q64, ghi vài mẫu rồi bấm DUMP để kiểm tra dữ liệu lưu.
7. Giữ DUMP 3 giây để kiểm tra xóa flash.


