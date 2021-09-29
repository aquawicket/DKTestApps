CPP_DK_Create("DKWindow")
CPP_DK_Create("DKRml")

let ele = document.createElement("div")
ele.setAttribute("test", "testvalue")
ele.id = "element1"
ele.style.width = "100px"
ele.style.height = "100px"
//ele.style.backgroundColor = "rgb(200,0,0)"
document.body.appendChild(ele)