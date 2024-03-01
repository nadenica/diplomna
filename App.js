import React from 'react';
import {createNativeStackNavigator} from '@react-navigation/native-stack';
import { View, Text } from 'react-native';
import Home from "./pages/Home.js"
import _camera from "./pages/camera.js"
import {NavigationContainer} from '@react-navigation/native';



const Stack = createNativeStackNavigator();

const MyStack = () => {
  return (
    <NavigationContainer>
      <Stack.Navigator>
        <Stack.Screen name={"Home"} component={Home} />
        <Stack.Screen name={"_camera"} component={_camera} />
      </Stack.Navigator>
    </NavigationContainer>
  );
};

export default MyStack;