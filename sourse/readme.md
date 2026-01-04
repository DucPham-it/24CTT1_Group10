# THÔNG TIN THÀNH VIÊN NHÓM:

| STT | MSSV     | Họ và tên              | 
|-----|----------|------------------------|
| 1   | 24120176 | Huỳnh Văn Đương        | 
| 2   | 24120469 | Chế Nguyễn Thuỳ Trang  | 
| 3   | 24120006 | Đào Thanh Phong        | 
| 4   | 24120251 | Huỳnh Bá Thi           | 
| 5   | 24120041 | Phạm Võ Đức            | 
| 6   | 24120506 | Phan Thế Minh Trí      | 

---
# TÊN ĐỀ TÀI
**TURN BASE CARD GAME**

---

## MÔ TẢ NGẮN GỌN ĐỀ TÀI

**Tọa Sát Bát Đồ** là một trò chơi đối kháng theo lượt (Turn-based Combat Game), trong đó người chơi điều khiển nhân vật **Hakari** chiến đấu với các Boss AI có độ khó tăng dần.  
Trò chơi được xây dựng theo mô hình **Object-Oriented Programming (OOP)**, chia rõ các **State**, **Game Object**, **Battle System** và **AI Decision System**.

Người chơi luôn là người đi trước. Mỗi lượt chơi được chia thành nhiều giai đoạn, kết hợp giữa **quản lý tài nguyên**, **chiến thuật thẻ bài** và **yếu tố may rủi (Jackpot)**.

---

## CÁC CHỈ SỐ CƠ BẢN

Cả người chơi và Boss đều có các chỉ số sau:
- **Máu (HP)**
- **Sát thương cơ bản (Base Damage)**
- **Thanh nộ (Rage / Jackpot Gauge)**

---

## CẤU TRÚC LƯỢT CHƠI CỦA NGƯỜI CHƠI (HAKARI)

Mỗi lượt của người chơi gồm **3 phần chính**:

### Phần 1: Phân bổ Chú Lực
- Hakari có **5 điểm chú lực** mỗi lượt.
- Người chơi lựa chọn phân bổ vào:
  - **Tấn công**
  - **Phòng thủ**
  - **Thanh nộ**

Quy tắc:
- Mỗi **1 điểm tấn công** → tăng **10% sát thương gây ra**
- Mỗi **1 điểm phòng thủ** → giảm **10% sát thương nhận vào**
- **Thanh nộ tối đa: 36 điểm**
- Mỗi **1 điểm thanh nộ** → tăng **2% tỉ lệ trúng Jackpot**

---

### Phần 2: Chọn Bài
- Hệ thống rút **ngẫu nhiên 6 lá bài** từ bộ bài.
- Người chơi **chọn 3 lá** để sử dụng trong lượt đó.

#### Phân loại thẻ bài

**1. Nhóm Hiệu Ứng**
- Lá 1: +3 điểm vào thanh nộ
- Lá 2: Quay Jackpot
- Lá 3: Quay Jackpot **2 lần**

**2. Nhóm Phòng Thủ**
- Lá 1: Phòng thủ thường (hiệu quả cao nhất)
- Lá 2: Phòng thủ + cộng 1 điểm thanh nộ
- Lá 3: 60% né chiêu

**3. Nhóm Gây Sát Thương**
- Lá 1: Tấn công thường (sát thương cao hơn trung bình)
- Lá 2: Gây sát thương + làm choáng đối thủ 1 lượt
- Lá 3: Tấn công phá giáp

---

### Phần 3: Quay Jackpot (nếu có)
- Nếu **trúng Jackpot**:
  - Trong **5 lượt tiếp theo**, Hakari:
    - Hồi **100% máu mỗi lượt**
    - **Bỏ qua Phần 1**
    - Tự động dồn **toàn bộ 5 điểm chú lực vào tấn công**
  - **Lần đầu trúng Jackpot**, đối thủ bị **choáng 1 lượt**

---

## CẤU TRÚC LƯỢT CHƠI CỦA BOSS (AI)

Boss cũng có **P1 và P2** tương tự người chơi, tuy nhiên:

### Khác biệt chính:
- Boss **chỉ phân bổ điểm cho Tấn công và Phòng thủ**
- **Không có thẻ nhóm Hiệu Ứng**
- Thanh nộ của Boss dùng để **kích hoạt Chiêu Thức**
- Thanh nộ:
  - Tự động +1 điểm sau mỗi vòng
  - Khi đầy → dùng chiêu → reset về 0

---

## CÁC BOSS & ĐỘ KHÓ

### Dễ – **Charles Bernard**
- **Nội tại – Chiến Trượng G**:  
  Cứ mỗi **3 lượt**, Charles tự động **né chiêu**
- **Chiêu thức**: Không có

---

### Trung Bình – **Kashimo**
- **Nội tại – Huyễn Thú Hổ Phách**:  
  Không dùng thuật thức, nhưng **sát thương và phòng thủ cơ bản rất cao**
- **Chiêu thức**:  
  Khi thanh nộ đầy (sau **4 lượt**), tung **tia sét gây sát thương cực lớn**

---

### Khó – **Uraume**
- **Nội tại – Băng Ngưng Chú Pháp**:
  - Khi Hakari trúng Jackpot:
    - Máu mỗi lượt chỉ hồi = máu hiện tại + 500 (không hồi đầy)
  - Chiêu thức của Uraume **giảm 40% phòng thủ của Hakari**
- **Chiêu thức**:
  - Khi thanh nộ đầy (sau **2 lượt**):
    - Nếu Hakari dồn **>1 điểm chú lực vào tấn công**, Uraume tạo **cột băng** ngăn Hakari tấn công

---

## Ý NGHĨA 

Đề tài áp dụng rõ các khái niệm:
- **Encapsulation**: quản lý chỉ số, thẻ bài, trạng thái
- **Inheritance & Polymorphism**: các Boss AI kế thừa từ lớp AI cơ sở
- **State Pattern**: Menu, NewGame, Battle, GameOver
- **Strategy Pattern**: AI Decision System cho từng Boss
- **Resource Management**: quản lý âm thanh, texture, deck bài

---

# CÔNG VIỆC THỰC HIỆN

## 24120176 - Huỳnh Văn Đương      

## 24120469 - Chế Nguyễn Thuỳ Trang  

## 24120006 - Đào Thanh Phong         

## 24120251 - Huỳnh Bá Thi          

## 24120041 - Phạm Võ Đức         

## 24120506 - Phan Thế Minh Trí   


# TỈ LỆ CHIA ĐIỂM

| STT | MSSV     | Họ và tên              | Tỉ Lệ
|-----|----------|------------------------|--------|
| 1   | 24120176 | Huỳnh Văn Đương        |   |
| 2   | 24120469 | Chế Nguyễn Thuỳ Trang  |   |
| 3   | 24120006 | Đào Thanh Phong        |   |
| 4   | 24120251 | Huỳnh Bá Thi           |   |
| 5   | 24120041 | Phạm Võ Đức            |   |
| 6   | 24120506 | Phan Thế Minh Trí      |   |

---

# HƯỚNG DẪN BIÊN DỊCH VÀ VẬN HÀNH 
## BIÊN DỊCH
Tại Folder tổng thực hiện lệnh:

```Bash
g++ -std=gnu++23 `
 (Get-ChildItem -Recurse -Filter *.cpp | % FullName) `
 -I./sourse/SFML/include `
 -L./sourse/SFML/lib `
 -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio `
 -o ./release/ToaSatBatDo.exe
```
## Vận Hành
Tại Folder tổng thực hiện lệnh:
```Bash
cd ./release
./ToaSatBatDo.exe
```
---

# VIDEO DEMO
Link:
```
abc
```

