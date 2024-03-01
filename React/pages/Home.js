import { useState, useEffect } from 'react'

import { NativeWindStyleSheet } from 'nativewind'
import * as FileSystem from 'expo-file-system' // Import FileSystem from Expo

NativeWindStyleSheet.setOutput({ default: 'native' })

const Home = ({ navigation, route }) => {
  const [tokens, setTokens] = useState(0)

  useEffect(() => {
    initializeFile()
    readFileAndParseNumber() // Read the file and update tokens state
  }, [])

  const initializeFile = async () => {
    try {
      const filename = FileSystem.documentDirectory + 'numbers.txt'
      const fileExists = await FileSystem.getInfoAsync(filename) // Check if file exists
      if (!fileExists.exists) {
        // If file doesn't exist, create it with initial value
        await saveFile(0)
      }
    } catch (error) {
      console.error('Error initializing file:', error)
    }
  }

  const saveFile = async (number) => {
    try {
      setTokens(number)
      const filename = FileSystem.documentDirectory + 'numbers.txt'
      const numberAsString = number.toString() // Convert the number to a string
      await FileSystem.writeAsStringAsync(filename, numberAsString)
      console.log('File saved successfully!')
    } catch (error) {
      console.error('Error saving file:', error)
    }
  }

  const readFileAndParseNumber = async () => {
    try {
      const filename = FileSystem.documentDirectory + 'numbers.txt'
      const fileContent = await FileSystem.readAsStringAsync(filename)
      const parsedNumber = parseInt(fileContent) // Parse the file content to an integer
      setTokens(parsedNumber) // Update the tokens state with the parsed number
    } catch (error) {
      console.error('Error reading file:', error)
    }
  }

  useEffect(() => {
    if (route.params && route.params.scannedData) {
      const newTokens = tokens + route.params.scannedData // Add scanned data to current tokens
      setTokens(newTokens) // Update tokens state
      saveFile(newTokens) // Save the updated tokens to file
    }
  }, [route.params])

  return (
    <View className="flex-1 items-center bg-gray-600 justify-between p-8">
      {/* Text section */}
      <View className="mt-8 items-center justify-around">
        <Text className="text-xl text-white">Number of tokens:</Text>
        <Text className="text-9xl text-white font-bold">{tokens}</Text>
      </View>

      {/* Button section */}
      <View style={{ width: '100%', justifyContent: 'flex-end' }}>
        <TouchableOpacity
          style={{ flexDirection: 'row' }}>

          {/* First Half of the Button (3:1) */}
          <View style={{ flex: 3 }}>
            <TouchableOpacity
              className="bg-black h-12 rounded-l-lg justify-center items-center border-r mb-4"
              onPress={() => { navigation.navigate('_camera') }}>
              <Text className="text-lg text-white">Scan QR code</Text>
            </TouchableOpacity>
          </View>

          {/* Second Half of the Button (3:1) */}
          <View style={{ flex: 1 }}>
            <TouchableOpacity
              className="bg-gray-700 h-12 rounded-r-lg justify-center items-center mb-4"
              onPress={() => { saveFile(0) }}>
              <Text className="text-lg text-white">redeem</Text>
            </TouchableOpacity>
          </View>
        </TouchableOpacity>
      </View>
    </View>
  )
}
/*
      <TouchableOpacity
        className="bg-black w-screen h-[50px] rounded-3xl justify-center items-center border mb-4"
        onPress={() => { navigation.navigate('_camera'); }}>
        <Text className="text-xl text-white">Scan QR code to earn tokens!</Text>
      </TouchableOpacity>
      <TouchableOpacity
        className="bg-black w-screen h-[50px] rounded-3xl justify-center items-center border mb-4"
        onPress={() => { saveFile(0); }}>
        <Text className="text-xl text-white">set tokens to 0!</Text>
      </TouchableOpacity> */
export default Home
