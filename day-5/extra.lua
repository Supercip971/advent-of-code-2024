function ReadInput()
    local file = io.open("input.txt", "r")
    local input = file:read("*a")
    file:close()
    return input
end




function DecodeRuleset (input_data)

    local result = {}
    local ruleset = {}
    local decoded_instruction = {}
    for line in input_data:gmatch("[^\n]+") do
        if line:len() > 7 then
            break
        end
        
        local rule = {}
        rule.left = line:sub(1, 2)
        rule.right = line:sub(4, 5)

        print("rule: ", rule.left, " must be printed before: " , rule.right)
        ruleset[#ruleset + 1] = rule
    end

    result.ruleset = ruleset

    local startDecoding = false
    
    for line in input_data:gmatch("[^\n]+") do
        if line:len() > 7 then
            startDecoding = true
        end

        if startDecoding then
            local instruction = {}
            for i in line:gmatch("[^,]+") do
                instruction[#instruction + 1] = i
            end


            decoded_instruction[#decoded_instruction + 1] = instruction
        end
    end

    result.decoded_instruction = decoded_instruction

    return result
end

function MapRuleset(ruleset) 
    local BeforeMap = {} -- A|B key: A value: B
    local AfterMap = {}
    for i, rule in ipairs(ruleset) do
        if BeforeMap[rule.left] == nil then
            BeforeMap[rule.left] = {}
        end
        BeforeMap[rule.left][#BeforeMap[rule.left] + 1] = rule.right

        if AfterMap[rule.right] == nil then
            AfterMap[rule.right] = {}
        end
        AfterMap[rule.right][#AfterMap[rule.right] + 1] = rule.left
    end

    local res = {}
    res.beforeVal = BeforeMap
    res.afterVal = AfterMap
    return res
end

function CheckInstructionPage(instruction, i, ruleset)
    
    -- checking from start to i 


    local result = {}
    
    local v = instruction[i]

    local AllowedBefore = ruleset.afterVal[v]
    if AllowedBefore ~= nil then
        for j = 1, i - 1 do

            local foundAllowance = false
            local current = instruction[j]
            for k, value in ipairs(AllowedBefore) do
                if value == current then
                    foundAllowance = true
                end
            end

            if not foundAllowance then
                result.left = j
                result.right = i
                result.success = false
                return result
            end
        end
    end    
    
    local AllowedAfter = ruleset.beforeVal[v]
    if AllowedAfter ~= nil then
        for j = i + 1, #instruction do
            local foundAllowance = false
            local current = instruction[j]
            for k, value in ipairs(AllowedAfter) do
                if value == current then
                    foundAllowance = true
                end
            end

            if not foundAllowance then
                result.left = i
                result.right = j
                result.success = false

                return result
            end
        end
    end
    result.left = 0
    result.right = 0
    result.success = true

    return result

end

function CheckInstruction(instruction, ruleset)
    
    for j, value in ipairs(instruction) do
        local current = value
        local result = CheckInstructionPage(instruction, j, ruleset)
        if not result.success then 
            return result
        end        
    end

    local result = {}
    result.left = 0
    result.right = 0
    result.success = true
    return result
end

function CheckAndFix(instruction, ruleset)

    local finalResult = {}
    local result = CheckInstruction(instruction, ruleset)
    if result.success then
        finalResult.success = true
        return finalResult
    end

    while not result.success do
        local left = result.left
        local right = result.right

        local temp = instruction[left]
        instruction[left] = instruction[right]
        instruction[right] = temp

        result = CheckInstruction(instruction, ruleset)
    end

    finalResult.success = false 
    finalResult.fixed = instruction
    return finalResult
end



print("- * - Day 5 - * -")

local data = ReadInput() 

local decodedData = DecodeRuleset(data)


print("Decoded ruleset: ")
for i, rule in ipairs(decodedData.ruleset) do
    print(rule.left, " must be printed before: ", rule.right)
end

print("Decoded instructions: ")
for i, instruction in ipairs(decodedData.decoded_instruction) do
    print("Instruction n°:", i)
    for j, value in ipairs(instruction) do
        print(value)
    end
end

local mappedRuleset = MapRuleset(decodedData.ruleset)

local ValidInstruction = {}

local summedCenter = 0  
for i, instruction in ipairs(decodedData.decoded_instruction) do

    local valid = CheckAndFix(instruction, mappedRuleset)
    print("Instruction n°:", i, "result: ", valid.success)

    if not valid.success then
        summedCenter = summedCenter+ valid.fixed[#valid.fixed//2+1]
    end

end


print("Summed center: ", summedCenter)
