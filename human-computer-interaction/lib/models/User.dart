// ignore: file_names

class Pet {
  String petPhoto;
  String name;

  Pet({
    required this.name,
    required this.petPhoto
  });
}

class User {
  String username;
  String firstName;
  String lastName;
  String location;
  String picture;
  int rating;
  int distance;
  int numOfReviews;
  String availableFrom;
  String availableTo;
  List<String> pettingServices;
  List<Pet> pets;
  String about;
  bool favourite;
  bool isOnline;

  //Constructor
  User({
    required this.username,
    required this.firstName,
    required this.lastName,
    required this.location,
    required this.picture,
    required this.rating,
    required this.distance,
    required this.numOfReviews,
    required this.availableFrom,
    required this.availableTo,
    required this.pettingServices,
    required this.pets,
    required this.about,
    required this.favourite,
    required this.isOnline
  });
}