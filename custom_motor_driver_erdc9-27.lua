-- Rover motor driver for a skid steering vehicle (i.e. the frame has separate throttle and steering controls)
--
-- The following parameters should be set:
--     SERVO1_FUNCTION = 94 (Script 1) PROPS
--     SERVO3_FUNCTION = 96 (Script 3)

--     SERVO2_FUNCTION = 95 (Script2) DRIVE MOTORS
--     SERVO5_FUNCTION = 97 (Script4)

--STORAGE FOR SERIAL DATA
local file_name = 'raw serial dump.txt'
local file_name_plain = 'serial dump.txt'
-- make a file
local file = assert(io.open(file_name, "a"),"Could not create file " .. file_name)
file = assert(io.open(file_name_plain, "a"),"Could not create file " .. file_name)
file:close()
local timer = 0

local interesting_data = {}
local roll = 1

--these are the scripting serial ports we will use to send our high level steering control to.
local K_SCRIPTING1 = 94 -- for steering control
local K_SCRIPTING2 = 95 -- for steering control
local K_SCRIPTING3 = 96 -- for throttle control
local K_SCRIPTING4 = 97 -- for steering control

local CONTROL_OUTPUT_THROTTLE = 3
local CONTROL_OUTPUT_YAW = 4

--find serial port
local port = serial:find_serial(0)
port:begin(115200)
port:set_flow_control(0)


--bool to hold water state
local detectWater = 0;
local finalData = 0;
function update()
local read = ""
  timer = timer+1
  --reads serial packet and stores water sensor state, syringe state, and data from the potentiostat into a text file. ( example packet: W0S4D125) 
  if port:available() > 0 then
      file = io.open("raw serial dump.txt","a")

      read = port:read()
      if(read==87) then
      file:write((millis()/1000):tofloat())
      file:write(':')
      file:write("Water: ")
      read = port:read()
      detectWater = read
      file:write(read)
      elseif(read == 83) then
        file:write(" State: ")
        read = port:read()
        file:write(read)
      elseif(read == 68)then
        file:write(" Data: ")
        read = port:read()
        finalData = read
        file:write(read)
        file:write("\n")
      end
    file:close()
    gcs:send_text(0,finalData)
    gcs:send_named_float('Sensor1', finalData)
    local speed = gps:ground_speed(gps:primary_sensor())
    gcs:send_named_float('Sensor2',speed)
  end 
  
  --
  --logger.write('SCR','Sensor1','f',table.unpack(interesting_data))

  -- if not armed, move steering and throttle to mid for safety
  if not arming:is_armed() then
    
    SRV_Channels:set_output_norm(K_SCRIPTING1, 0)
    SRV_Channels:set_output_norm(K_SCRIPTING3, 0)
    SRV_Channels:set_output_norm(K_SCRIPTING2, 0)
    SRV_Channels:set_output_norm(K_SCRIPTING4, 0)
  else
    -- retrieve high level steering and throttle control outputs from vehicle in -1 to +1 range
    local steering = vehicle:get_control_output(CONTROL_OUTPUT_YAW)
    local throttle = vehicle:get_control_output(CONTROL_OUTPUT_THROTTLE)

    --reverse switch
    if(rc:get_pwm(9)>1200)then
        throttle = -throttle
    end

    if(rc:get_pwm(15)>1200)then
      port:write('a')
    else
      port:write('b')
     end

    --convert from ackerman to skid steering
    if (steering and throttle) then
      if (throttle < 0) then
          steering = -steering
      end
      local summed = steering+throttle
      local diff = throttle-steering
    if(diff<-1) then 
      diff = -1
    end
    if(diff>1) then
        diff = 1
    end
    if(summed<-1) then 
        summed = -1
      end
      if(summed>1) then
          summed = 1
      end
    --end of convert steering
    
    --check switches to enable/disable the drive motors and propellors (3 states). if water is detected, only the propellors will work. 
    if(rc:get_pwm(7)<1100 and not (detectWater==1)) then
        SRV_Channels:set_output_norm(K_SCRIPTING1, 0)
        SRV_Channels:set_output_norm(K_SCRIPTING3, 0)
        SRV_Channels:set_output_norm(K_SCRIPTING2, diff)
        SRV_Channels:set_output_norm(K_SCRIPTING4, summed)
    elseif(rc:get_pwm(7)<1600 and ((detectWater==0) or stuck == 1))then
        SRV_Channels:set_output_norm(K_SCRIPTING1, diff)
        SRV_Channels:set_output_norm(K_SCRIPTING3, summed)
        SRV_Channels:set_output_norm(K_SCRIPTING2, diff)
        SRV_Channels:set_output_norm(K_SCRIPTING4, summed)
    elseif(rc:get_pwm(7)<2200 or (detectWater==1))then
        SRV_Channels:set_output_norm(K_SCRIPTING1, diff)
        SRV_Channels:set_output_norm(K_SCRIPTING3, summed)
        SRV_Channels:set_output_norm(K_SCRIPTING2, 0)
        SRV_Channels:set_output_norm(K_SCRIPTING4, 0)
    end

    --TODO: ADD SWITCH FUNCTIONALITY THAT CAN BE UTILIZED IN AUTO MODE

    --get the GPS ground speed.
    local speed = gps:ground_speed(gps:primary_sensor())
    --local gps_speed_accuracy = gps:speed_accuracy()
    local target_speed = (rc:get_pwm(10)-500)/1000
    gcs:send_named_float('Sensor3',target_speed)
    if(not speed)then
      speed =0
    end
    



    --check if speed or throttle is over/under threshold values
    --if so, timer is reset and bot is NOT STUCK
    if(speed>target_speed or throttle < 0.25)then
      timer = 0
      stuck = 0
      
    end

    --if timer expires and we are in the water, change stuck to 1
    --when stuck == 1, both the drive motors and the propellor motors are enabled.
    if(detectWater == 1 and timer >100)then
      stuck = 1
      timer = 0
    end

    --print if stuck
    if(stuck == 0)then
      gcs:send_text(0,"NOT STUCK")
    else
      gcs:send_text(0,"STUCK")
    end
end  
end
  return update, 20-- run at 50hz
end

gcs:send_text(6, "rover-motor-driver.lua is running")
return update()