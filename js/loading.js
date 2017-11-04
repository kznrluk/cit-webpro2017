socket.on('message', addMessage(data))

function addMessage (msg) {
    var domMeg = document.createElement('div');
    domMeg.innerHTML = new Date().toLocaleTimeString() + ' ' + msg;
    msgArea.appendChild(domMeg);
  }