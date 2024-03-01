import React, { useState, useEffect } from 'react';
import { Text, View, TouchableOpacity } from 'react-native';
import { BarCodeScanner } from 'expo-barcode-scanner';

export default function _camera({ navigation }) {
  const [hasPermission, setHasPermission] = useState(null);
  const [scanned, setScanned] = useState(false);

  useEffect(() => {
    const getBarCodeScannerPermissions = async () => {
      const { status } = await BarCodeScanner.requestPermissionsAsync();
      setHasPermission(status === 'granted');
    };

    getBarCodeScannerPermissions();
  }, []);

  const handleBarCodeScanned = ({ type, data }) => {
    setScanned(true);
    const returned = parseInt(data);
    //alert(`Bar code with type ${type} and data ${data} has been scanned! return = ${returned}`);
    navigation.navigate('Home', { scannedData: returned }); // Pass scanned data to Home screen
  };

  if (hasPermission === null) {
    return <Text className="bg-yellow-400">Requesting for camera permission</Text>;
  }
  if (hasPermission === false) {
    return <Text>No access to camera</Text>;
  }

  if (hasPermission === true) {
    return (
      <View className="w-screen h-screen bg-white-600 items-center">
        {!scanned && <Text className="text-3xl text-black">Show the barcode</Text>}
        <BarCodeScanner
          onBarCodeScanned={scanned ? undefined : handleBarCodeScanned}
          className="w-screen h-[500px]"
        />

        {scanned && <TouchableOpacity
          className="bg-black w-screen h-[50px] rounded-3xl justify-center items-center border mb-4"
          onPress={() => setScanned(false)}>
          <Text className="text-xl text-white">Click to rescan</Text>
        </TouchableOpacity>
        }

        <TouchableOpacity
          className="bg-black w-screen h-[50px] rounded-3xl justify-center items-center border mb-4"
          onPress={() => { navigation.navigate('Home'); }}>
          <Text className="text-xl text-white">Go back</Text>
        </TouchableOpacity>

      </View>
    );
  }
}
