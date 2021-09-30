CPP_DK_Create("DKWindow")
CPP_DK_Create("DKRml")

let ele = document.createElement("div")
ele.id = "idvalue"
ele.setAttribute("class", "classvalue")
ele.setAttribute("test", "testvalue")
ele.style.display = "block"
ele.style.width = "100px"
ele.style.height = "100px"
//ele.style.backgroundColor = "black"
document.body.appendChild(ele)



ele.ele2 = document.createElement("div")
ele.ele2.id = "idvalue2"
//ele.ele2.setAttribute("class", "classvalue2")
ele.ele2.setAttribute("myAttribute", "myAttributeValue")
ele.ele2.style.position = "absolute"
ele.ele2.style.display = "block"
ele.ele2.style.width = "66px"
ele.ele2.style.height = "66px"
//ele.ele2.style.backgroundColor = "white";
ele.appendChild(ele.ele2)