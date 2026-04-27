````md
# Adafruit Fingerprint Sensor Library (Arduino)

A practical guide to using the Adafruit Fingerprint Sensor Library with Arduino (R305 / AS608 / GT-521F modules).

This document explains:
- Functions available
- Working principle
- Usage examples
- Enrollment and matching flow

---

# Overview

The `Adafruit_Fingerprint` library allows Arduino to communicate with fingerprint sensors using UART (serial communication).

Key idea:
The sensor handles:
- Image capture
- Feature extraction
- Matching
- Storage

Arduino only sends commands.

---

# Setup

## Include libraries
```cpp
#include <Adafruit_Fingerprint.h>
#include <SoftwareSerial.h>
````

## Initialize sensor

```cpp
SoftwareSerial mySerial(2, 3); // RX, TX
Adafruit_Fingerprint finger(&mySerial);
```

## Start communication

```cpp
finger.begin(57600);
```

## Check connection

```cpp
if (finger.verifyPassword()) {
  Serial.println("Sensor Found");
} else {
  Serial.println("Sensor Not Found");
}
```

---

# Fingerprint Functions

---

## getImage()

```cpp
finger.getImage();
```

Description:
Captures fingerprint image when a finger is placed.

Returns:

* FINGERPRINT_OK → success
* FINGERPRINT_NOFINGER → no finger detected
* FINGERPRINT_PACKETRECIEVEERR → communication error

---

## image2Tz(slot)

```cpp
finger.image2Tz(1);
```

Description:
Converts fingerprint image into a digital template.

Slots:

* 1 → first scan
* 2 → second scan (enrollment)

---

## fingerSearch()

```cpp
finger.fingerSearch();
```

Description:
Searches stored fingerprints for a match.

Returns:

* FINGERPRINT_OK → match found
* FINGERPRINT_NOTFOUND → no match

Extra data:

```cpp
finger.fingerID
finger.confidence
```

---

# Enrollment Functions

---

## createModel()

```cpp
finger.createModel();
```

Description:
Combines two scans into one fingerprint model.

---

## storeModel(id)

```cpp
finger.storeModel(1);
```

Description:
Stores fingerprint in memory slot id.

---

## Full enrollment flow

```cpp
finger.getImage();
finger.image2Tz(1);

finger.getImage();
finger.image2Tz(2);

finger.createModel();
finger.storeModel(id);
```

---

# Delete Functions

---

## deleteModel(id)

```cpp
finger.deleteModel(1);
```

Deletes a specific fingerprint.

---

## emptyDatabase()

```cpp
finger.emptyDatabase();
```

Deletes all stored fingerprints.

---

# System Info

---

## getTemplateCount()

```cpp
finger.getTemplateCount();
```

Returns number of stored fingerprints.

---

## getImageCapacity()

```cpp
finger.getImageCapacity();
```

Returns total storage capacity of the sensor.

---

# Example: Basic Working Code

```cpp
#include <Adafruit_Fingerprint.h>
#include <SoftwareSerial.h>

SoftwareSerial mySerial(2, 3);
Adafruit_Fingerprint finger(&mySerial);

void setup() {
  Serial.begin(115200);
  finger.begin(57600);

  if (finger.verifyPassword()) {
    Serial.println("Sensor OK");
  } else {
    Serial.println("Sensor FAIL");
  }
}

void loop() {
  if (finger.getImage() != FINGERPRINT_OK) return;

  if (finger.image2Tz(1) != FINGERPRINT_OK) return;

  if (finger.fingerSearch() == FINGERPRINT_OK) {
    Serial.print("ID: ");
    Serial.println(finger.fingerID);
  } else {
    Serial.println("No match");
  }

  delay(1000);
}
```

---

# Working Principle Summary

* Sensor captures fingerprint image
* Converts image into features
* Stores features in internal memory
* Matches live scan with stored templates
* Returns matched ID and confidence score

Arduino only sends commands; sensor performs all processing internally.

```
```

