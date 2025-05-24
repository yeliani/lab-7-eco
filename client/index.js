let socket = io("http://localhost:5050/", { path: "/real-time" });

document.getElementById("turn-on-button").addEventListener("click", turnOnLed);
document.getElementById("turn-off-button").addEventListener("click", turnOffLed);
const body = document.querySelector("body");

async function turnOnLed() {
  socket.emit("turn-on"); // Sends a string message to the server
}

async function turnOffLed() {
  socket.emit("turn-off"); // Sends a string message to the server
}

const ledSwitch = document.getElementById("miSwitch");
ledSwitch.addEventListener("change", () => {
    if (ledSwitch.checked) {
      socket.emit("turn-on");
    } else {
      socket.emit("turn-off");
    }
  });


socket.on("porValue", (data) => {
  console.log(data);
  const potValue = data?.potValue ?? 0;
  const potValue2 = data?.potValue2 ?? 0;
  const btnValue = data?.btnValue ?? 1;

  const brightness = Math.floor((potValue / 255) * 255);
  document.body.style.backgroundColor = `rgb(${brightness}, ${brightness}, ${brightness})`;
  document.body.style.color = "rgb(17, 53, 216)"

    if (btnValue === 0) {
    ledSwitch.checked = true;

    if (!document.getElementById("messaje")) {
      const mensaje = document.querySelector(".message");
      const saludo = document.createElement("div");
      saludo.id = "mensaje";
      saludo.innerText = "Hola amigo";
      saludo.style.fontSize = "1rem";
      saludo.style.color = "white";
      saludo.style.marginTop = "1rem";
      mensaje.appendChild(saludo);
    }

   setTimeout(() => {
      ledSwitch.checked = false;
      socket.emit("turn-off");

      const mensaje = document.getElementById("mensaje");
      if (mensaje) mensaje.remove();
    }, 500);
  }

  const barra = document.getElementById("barra-potenciometro");
  const nivel = data?.potValue2 ?? 0; 
  const altura = Math.floor((nivel / 255) * 100);
  barra.style.height = `${altura}%`; 

  if (nivel < 100) {
    barra.style.background = "linear-gradient(to top, #00c853, #b2ff59)"; // Verde
  } else if (nivel < 180) {
    barra.style.background = "linear-gradient(to top, #ffd600, #ffeb3b)"; // Amarillo
  } else {
    barra.style.background = "linear-gradient(to top, #d50000, #ff5252)"; // Rojo
  }
});
  
