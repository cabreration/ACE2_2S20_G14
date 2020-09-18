let common = require('../arduino/common')

module.exports = (app, aws_utils) => {
    app.get('/data', (req, res) => {
        
        // avg times
        let docClient = new aws_utils.AWS.DynamoDB.DocumentClient()
        let params = {
            TableName: 'Automail_TravelTimes'
        }

        docClient.scan(params, (err, data) => {
            if (err) console.log(err)
            else {
                let go = 0
                let go_count = 0
                let come = 0
                let come_count = 0
                data.Items.forEach(record => {
                    if (record.state == 1) {
                        go_count++
                        go += Number(record.time)
                    }
                    else {
                        come_count++
                        come += Number(record.time)
                    }
                });  
                    
                common.total_delivered = go_count
                common.avg_go = go/(go_count > 0 ? go_count : 1)
                common.avg_come = come/(come_count > 0 ? come_count : 1)
            }
        })

        let docClient2 = new aws_utils.AWS.DynamoDB.DocumentClient()
        let params2 = {
            TableName: 'Automail_Delivery'
        }

        docClient2.scan(params2, (err, data) => {
            if (err) console.log(err)
            else {
                let weight = 0
                let weight_count = 0
                let obs_count = 0
                data.Items.forEach(record => {
                    weight += Number(record.weight)
                    weight_count++
                    obs_count += Number(record.obstacles)
                });  
                    
                common.avg_weight = weight/(weight_count > 0 ? weight_count : 1)
                common.total_obstacles = obs_count
            }
        })
        
        setTimeout(() => {
            response = {
                obstacles: common.obstacles.toString(),
                state: common.state,
                avg_go: common.avg_go.toString(),
                avg_come: common.avg_come.toString(),
                total_obstacles: common.total_obstacles.toString(),
                avg_weight: common.avg_weight.toString(),
                total_delivered: common.total_delivered.toString()
            }
            res.send(response)
        }, 3000)
    })
}