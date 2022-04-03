# [sensortemperatura]

Sensor de temperatura.

## Integrantes del equipo

Carlos Martínez Marcos,
Adrián  Paino,
Víctor Malumbres Muñoz.

## Objetivos del trabajo

Vamos a crear un software que permita detectar la temperatura de una habitación y almacenar los valores de esta. Usaremos un sensor para medir la temperatura y almacenaremos los valores obtenidos en un programa que crearemos. También usaremos la información obtenida para añadir algunas utilidades extra, como implementar un mecanismo que ayude a enfriar la habitación en caso de que la temperatura sea demasiado elevada.
[Lista de los objetivos que se persiguen con el trabajo propuesto.]

## Identificacion de materiales

<br />Sensor

Los sensores de temperatura son ampliamente usados con Arduino, son unos pequeños dispositivos que nos permiten medir la temperatura del aire, líquidos o sólidos. A pesar que estas medidas son analógicas, estos sensores los tendremos que conectar a pines digitales, ya que la señal de salida es digital a un bus punto a punto. Permiten medir la temperatura mediante una señal eléctrica determinada. Dicha señal puede enviarse directamente o mediante el cambio de la resistencia. También se denominan sensores de calor o termosensores. Su rango de medición es desde 0°C a 50 °C, su precisión de medición de temperatura de ±2.0 °C y la resolución de temperatura de 0.1°C. Sin embargo en nuestra aplicación suponemos que oscilará entre los 20 y 40 grados celsius. Se usan bastante en proyectos de estaciones meteorológicas. En entornos mas peligrosos, son comunes los sensores sin contacto, los cuales detectan la temperatura basándose en la radiacion térmica emitida por una fuente de calor. Los sensores de temperatura de contacto, que son los que vamos a usar, deben hacer contacto con el objeto a medir. El principal inconveniente de este sensor es esto mismo, ya que a veces puede resultar incómodo mantener en contacto la placa con el objeto.

<br />Ventilador

Usaremos un ventilador que estará conectado al sensor de temperatura, para que funcione cuando la temperatura sobrepase ciertos niveles. Este tipo de actuadores suele ser barato y sencillo de usar. Sus proiedades son:
Voltaje de funcionamiento: 5 V.
Tamaño del tablero: 3,49 x 2,15 x 0,15 cm (aproximadamente).
Diámetro de la hélice: 7,5 cm (aproximadamente).

<br />led


