/** Outputs.ino
 * Sets port 7 on bank B to OUTPUT and toggles
 * its state every 250ms
 */
#include <Wire.h>
#include <mcp23017.h>

#define MCP_ADDR (0)
MCP23017 mcp(MCP_ADDR);

void setup(void) {
  Serial.begin(115200);
  Wire.begin(5, 6);
  mcp.start();
  mcp.pinMode(GPB7, OUTPUT);
}

void loop(void) {
  mcp.digitalWrite(GPB7, HIGH);
  delay(250);
  mcp.digitalWrite(GPB7, LOW);
  delay(250);
}
