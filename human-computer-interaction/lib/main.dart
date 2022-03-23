import 'package:flutter/material.dart';
import 'package:pet_alone/views/SittersListViewWidget.dart';
import 'package:pet_alone/views/ProfileWidget.dart';
import 'package:pet_alone/views/AllChatsWidget.dart';
import 'package:pet_alone/fakeDB.dart';

void main() => runApp(const PetAlone());

class Nav extends StatefulWidget {
  const Nav({Key? key}) : super(key: key);

  @override
  State<Nav> createState() => _NavState();
}

class _NavState extends State<Nav> {
  int _selectedIndex = 0;
  static const TextStyle optionStyle =
      TextStyle(fontSize: 30, fontWeight: FontWeight.bold);
  static List<Widget> _widgetOptions = <Widget>[
    SittersListViewWidget(),
    HomeScreen(),
    Text(
      'Index 2: School',
      style: optionStyle,
    ),
    ProfileWidget(user: FakeDB.users[2])
  ];

  void _onItemTapped(int index) {
    setState(() {
      _selectedIndex = index;
    });
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      body: _widgetOptions[_selectedIndex],
      bottomNavigationBar: BottomNavigationBar(
        unselectedItemColor: Colors.grey,
        fixedColor: Colors.blue,
        items: const <BottomNavigationBarItem>[
          BottomNavigationBarItem(
            icon: Icon(Icons.pets),
            label: 'Sitters',
          ),
          BottomNavigationBarItem(
            icon: Icon(Icons.message),
            label: 'Messages',
          ),
          BottomNavigationBarItem(
            icon: Icon(Icons.notifications),
            label: 'Notifications',
          ),
          BottomNavigationBarItem(
            icon: Icon(Icons.person),
            label: 'Profile',
          )
        ],
        currentIndex: _selectedIndex,
        
        onTap: _onItemTapped,
      ),
    );
  }
}


class PetAlone extends StatelessWidget {
  const PetAlone({Key? key}) : super(key: key);

  @override
  Widget build(BuildContext context) {

    return MaterialApp(
      theme: ThemeData(
        appBarTheme: const AppBarTheme()
      ),
      title: 'Pet Alone',
      home: Nav(),
      debugShowCheckedModeBanner: false);
  }
}