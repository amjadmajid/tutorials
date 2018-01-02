/********************
 Create an object
********************/

/* First option: using the dot notation
---------------------------------------*/
var audi = new Object();
// Object properties
audi.name = 'Audi';
audi.color ='Black';
audi.model =2018;
audi.fuelType;
// Object Methods
audi.setFuelType = function(ft){
  audi.fuelType = ft;
};
audi.getFuelType = function(){
  return audi.fuelType;
};

audi.setFuelType('benzene');
// console.log(audi);
console.log( audi.getFuelType() );


/* Second option: Using the colon notation
-----------------------------------------*/
var jaguar = new Object();
var jaguar = {
  name : 'jaguar',
  color : 'red',
  model : ' Jaguar 1965',
  setFuelType : function(ft) {
    feulType = ft;
  },
  getFuelType : function () {
    return feulType;
  }
};

console.log(jaguar);


/* Object constructor: declare a prototype and instantiate objects
-------------------------------------------------------------*/
function Car(name, color, model){
  this.name = name;
  this.color = color;
  this.model = model;
}

jaguar = new Car('Jaguar', 'red', '1965');
maserati = new Car('maserati', 'grey', '1955');

console.log(jaguar.name);       // Option 1 to call a property of an object
console.log(jaguar["color"]);   // Option 2 to call a property of an object
console.log(maserati);
