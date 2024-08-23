import Swal from "sweetalert2";

function NoticeIOS() {
  Swal.fire({
    title: "ผู้ใช้ Apple ทุกท่าน !",
    text: "ขอแจ้งให้ทราบว่าโปรเจค Home for All (SmartEnvision) ขณะนี้ยังไม่รองรับการใช้งานในระบบปฏิบัติการ iOS อย่างเป็นทางการ ดังนั้น หากท่านใช้งานผ่าน Android Emulator บนเครื่อง Apple จะไม่สามารถใช้งานฟีเจอร์บางอย่างได้อย่างเต็มประสิทธิภาพ",
    confirmButtonText: "เข้าใจแล้ว",
    color: "#ffffff",
    background: "#222222",
    confirmButtonColor: "#373737",
    showClass: {
      popup: `
        slide-in-blurred-bottom
      `,
    },
    hideClass: {
      popup: `
        slide-out-blurred-bottom
      `,
    },
  }).then((result) => {
    if (result.isConfirmed) {
      window.location.href =
        "https://github.com/FujaTyping/HfA-Project/blob/main/Envision-Appstore/Apple.md";
    }
  });
}

export { NoticeIOS };
