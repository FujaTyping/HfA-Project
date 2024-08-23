import Swal from "sweetalert2";

function NoticeIOS() {
  Swal.fire({
    title: "เตือน !",
    text: "โปรเจค Home for All (SmartEnvision) อยู่ระหว่างการพัฒนา ดังนั้น แอปพลิเคชันอาจมีบัคหรือข้อผิดพลาดในระหว่างการใช้งาน ขณะนี้กำลังพยายามปรับปรุงและแก้ไขเพื่อมอบประสบการณ์ที่ดีที่สุด",
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
