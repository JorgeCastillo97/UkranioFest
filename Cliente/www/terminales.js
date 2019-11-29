function actualiza() {
  console.log("actualiza src...");
  var dt = new Date();
  for (var i = primera; i <= ultima; i++) {
    if (existeImagen("imagenes/"+IDRED+i+".jpg")) {
      var source = "imagenes/"+IDRED+i+".jpg?"+dt.getTime();
      document.getElementById(IDRED + i).src= source;
    } else {
      document.getElementById(IDRED + i).src= "imagenes/vacio.jpg";
    }

  }
}

function existeImagen(url)
{
   var img = new Image();
   img.src = url;
   return img.height != 0;
}

var primera = 5, ultima = 35, IDRED="192.168.0.";

$(document).ready(function() {
  for(var i = primera; i <= ultima; i++){
    $("#lista_terminales").append(
      '<div class="col">' +
        '<h2 class="text-center">' + IDRED + i + '</h2>' +
      '</div>' +
      '<img class="center-img" height="60%" align="center" src="imagenes/vacio.jpg" id="' + IDRED + i +'" alt="'+ IDRED + i +'"' +
      '<br>'
    );
  }
  setInterval('actualiza()', 2000);
});
