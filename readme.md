
# Jungle Cruise - Cuộc phiêu lưu kỳ thú của chú khỉ
Abu - chú khỉ con vừa lớn với mong muốn khám phá thế giới rộng lớn ngoài kia, nhưng rừng rậm Amazon, với những nguy hiểm đầy rình rập và những loài quái vật nguy hiểm, liệu chú khỉ có thể vượt qua và đạt được mong muốn của mình, tìm kiếm được kho báu lớn nhất? Hãy cùng nhau giúp chú khỉ ấy nhé!

## Ảnh minh họa

![menu.png](https://up-anh.vi-vn.vn/img/1714121077_bcd94c39272f848e539e40710109c78e.png)

## Giới thiệu về game
- [0. Cách tải game](#0-cách-tải-game)
    * [a. Cách 1: Không bao gồm code.](#a-cách-1-không-bao-gồm-code)
    * [b. Cách 2: Bao gồm code và có thể biên dịch.](#b-cách-2-bao-gồm-code-và-có-thể-biên-dịch)
- [1. Bắt đầu game](#1bắt-đầu-game)
- [2. Các thành phần trong game:](#2-các-thành-phần-trong-game)
- [3. Cách chơi](#3-cách-chơi)
    * [a. Các loại thao tác](#acác-loại-cây)
    * [b. Các loại địch](#bcác-loại-zombie)
- [4. Chiến thắng và thất bại](#4-chiến-thắng-và-thất-bại)
- [Về đồ họa của game:](#về-đồ-họa-của-game)
- [Về source code game](#về-source-code-game)
# 0. Cách tải game
## a. Cách 1: Không bao gồm code.

Tải game (được nén thành .zip) tại link
sau: https://github.com/nmhienbn/PVZ-Kaito-NMH-Edition/releases/tag/published<br/>
Cách này tiết kiệm bộ nhớ và thời gian tải đi rất nhiều (khoảng 103MB).<br/>
Giải nén game vào một thư mục và bật pvz.exe lên và chơi.<br/>

## b. Cách 2: Bao gồm code và có thể biên dịch.

**Bước 1:** Clone repo này về (Khoảng 800 MB - do có cả lịch sử các phiên bản). <br/>
Hoặc Chọn Code -> Download Zip (Khoảng 90MB)

![image](resources/preview/download.png)

- Tất cả code đều nằm trong thư mục src.<br/>
- Có thể nhảy đến bước 5 để chơi luôn.

**Bước 2:** Cài mingw. Ở đây tôi cài đặt phiên bản MinGW-W64
GCC-8.1.0 [x86_64-posix-seh](https://sourceforge.net/projects/mingw-w64/files/Toolchains%20targetting%20Win64/Personal%20Builds/mingw-builds/8.1.0/threads-posix/seh/x86_64-8.1.0-release-posix-seh-rt_v6-rev0.7z/download).<br/>
Một số chú ý: <br/>

- Nếu sử dụng trình biên dịch khác thì phải dịch lại icon: vào thư mục icon rồi dùng
  lệnh `windres main.rc -O coff main.res` trong cmd.<br/>
- Phải xóa ba dll của c++ trong thư mục chứa pvz.exe: `libgcc_s_seh-1.dll`, `libstdc++-6.dll`, `libwinpthread-1.dll`. Ba
  dll này chỉ dành cho người chơi không cài sẵn c++ trong máy.

**Bước 3:** Cài GNU make

**Bước 4:** Mở cmd trong thư mục chứa Makefile và gõ lệnh make.

**Bước 5:** Bật pvz.exe và chơi
# 1. Bắt đầu game
Menu chính 

![Screenshot 2024-04-26 200015.png](https://up-anh.vi-vn.vn/img/1714136840_aba05f753becef44c52ff251f9f6009b.png)

- Chờ 1 chút rồi nhất nút "Start"; 
![Screenshot 2024-04-26 200520.png](https://up-anh.vi-vn.vn/img/1714136800_6609522ceb82aa02a3529ee0c7473003.png)
- Nếu có khó khăn hãy nhấn nút "Help";
![Screenshot 2024-04-26 200531.png](https://up-anh.vi-vn.vn/img/1714136839_044ce696aef429074c55f09d4d2ccaa0.png)
- Nếu cần thoát khỏi game, ấn "Quit";
![Screenshot 2024-04-26 200542.png](https://up-anh.vi-vn.vn/img/1714136839_95804f8590502b815ba91c92e30e4a7b.png)

# 2. Các thành phần trong game:
- Apple: Đơn vị tính điểm cho game, ăn được càng nhiều đồng nghĩa với điểm càng tăng 
![apple.png](https://up-anh.vi-vn.vn/img/1714136977_0502937e400c7a271368b26b4a623d83.png)
- Chỉ số sinh mệnh: Hiển thị số lần mà người chơi còn có thể chơi lại 
![mang.png](https://up-anh.vi-vn.vn/img/1714137014_5dd598957fa66a020ab27ebbcac26710.png)
- Score: Điểm bắn quái của nhân vật, càng bắn được nhiều quái, điểm càng tăng 
![menu.png](https://up-anh.vi-vn.vn/img/1714121077_bcd94c39272f848e539e40710109c78e.png)

# 3. Cách chơi
Nhảy vượt qua các chướng ngại vật, bắn quái săn điểm, nếu rơi xuống vực hoặc bị quái bắn sẽ bị trừ 1 điểm. 

## a. Các loại cây

Có 4 loại quái
- Quái thú Slime - chỉ có thể đứng yên, nếu người chơi chạm vào là -1 mạng và bị giảm tốc ![ocsen.png](https://up-anh.vi-vn.vn/img/1714137223_af14ade8358fe466390a1018093dace8.png)

- Quái thú Plant - có đạn, có thể bắn được người chơi ở tầm xa 3-4cm, nếu chạm vào hoặc bị trúng đạn sẽ -1 điểm
 ![Plant.png](https://up-anh.vi-vn.vn/img/1714137370_5f3949911851a6f46a6667f7d049a42a.png)
- Quái thú Trunk, giống Plant và có khả năng bắn đạn 
![Trunk.png](https://up-anh.vi-vn.vn/img/1714137427_0f4fd413e24795a93a0226120cf9cd63.png)
- Quái thú ong bắp cày - chỉ có thể đứng im, có khả năng bắn đạn theo chiều từ trên xuống
![Bee.png](https://up-anh.vi-vn.vn/img/1714137469_30d207e552fa66f9fb85aaa026808ff6.png)
- Quái thú chim - chỉ có thể bay, không có khả năng bắn đạn, đụng vào -1 mạng 
![Bird.png](https://up-anh.vi-vn.vn/img/1714137528_d234c607f4b2aaece7e08f781a787e63.png)


## b. Các phím chơi
- Click chuột trái để bắn lên trên 1 góc 45 độ
- Click chuột phải để bắn thẳng phải, trái
- Các phím lên xuống trái, phải vưới chức năng di chuyển nhân vật 
![menu1.png](https://up-anh.vi-vn.vn/img/1714137599_58f5366eb43552f8051490131f61ad07.png)
# 4. Điều đã học được
- Tìm hiểu về SDL2
- Tìm hiểu về SDL2_image,SDL2_mixer,SDL2_ttf
- Kĩ thuật TileMap, xử lý va chạm 
- Tạo dựng Menu 

---
### Về đồ họa của game:

- Chủ yếu lấy từ https://itch.io/game-assets/tag-jungle
- Có dùng Adobe Illustrator để chỉnh sửa sao cho phù hợp 

### Về source code game và credit:

- Tham khảo nguồn Run_Dino https://github.com/DXL64/FirstProject/tree/master/source;
- Ngoài ra còn có nguồn của Clb Lập trình Ptit https://www.youtube.com/watch?v=ANjk6LsShRo&list=PLZd7ojlRK0bwrL8060OGurG_kaeJc_QOH
- SDL2 Lazy Foo; 
- Sự trợ giúp của anh mentor; 

##Về source:
- File Base:+ Chứa hình ảnh enemies và nhân vật chính 
            + Menu
- File Font, Sound: Quản lý âm thanh và font chữ
- File map: Tile map 
- BulletObject: Quản lý các lớp đạn bắn của nhân vật chính và kẻ địch 
- CommonFunction: Quản lý các chức năng, xử lý va chạm 
- Dead: Quản lý mạng chơi của nhân vật chính 
- Game_map: Map của game
- Menu: + Button.cpp
        + ui.cpp


